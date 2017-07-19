import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Kodlio 1.0
import "../control"
import "../singleton"

Item {

    id                  :   mainContainer
    implicitWidth       :   700
    implicitHeight      :   400

    readonly property bool      localSearch     :   tabBar.currentIndex === 0
    readonly property string    filterText      :   nameFilterTxt.text

    function        filter(){
        if(localSearch)     filterLocal(filterText)
        else                filterOnline(filterText)
    }

    function        filterLocal(){
        localLibs.clear()
        libManager.filterLocalLibs(filterText)
    }

    function        filterOnline()  {
        onlineLibs.clear()
        libManager.filterOnlineLibs(filterText)
    }

    function        refreshLocalLibraries(){
        libManager.retrieveLocalLibraries()
    }

    function        removeSelectedLibrary(){
        var item = list.currentItem
        libManager.removeLibs([{ name : item.libName , version : item.libVersion }])
    }

    function        installSelectedLibrary(){
        var item = list.currentItem
        libManager.installLibs([{ name : item.libName , version : item.libVersion }])
        refreshLocalLibraries()
    }

    onLocalSearchChanged    :   filter()

    ArduinoLibManager   {

        id                                  :   libManager
        onLibInstallErrorOccurred           :   {
            var message = desc.name + " yuklenemedi."
            Global.displayMessage(message)
            Global.consoleErrorOutput(message)
        }
        onLibInstalledSuccessfully          :   toast.displayMessage(desc.name + " basariyla yuklendi.")
        onLibRemovedSuccessfully            :   toast.displayMessage(desc.name + " basariyla silindi.")
        onLibRemoveErrorOcurred             :   toast.displayMessage(desc.name + " silinirken hata olustu !")
        onRetrieveOnlineLibsInternetError   :   toast.displayMessage("Kutuphaneler alinamadi, internet baglantisini kontrol ediniz.")
        onOnlineLibsChanged                 :   filterOnline()
        onLocalLibsChanged                  :   filterLocal()
        onFilterLocalResult                 :   localLibs.append(item)
        onFilterOnlineResult                :   onlineLibs.append(item)
        onLibNotRemovable                   :   toast.displayError("Bu kütüphane silinemez.")

        Component.onCompleted               :   {
            libManager.retrieveOnlineLibraries()
            libManager.retrieveLocalLibraries()
        }
    }

    Toast{
        id              :   toast
        container       :   parent
        textColor       :   "white"
    }

    GenericMessageDialog{
        id              :   removeLibraryDialog
        title           :   "Kutuphaneyi sil"
        message         :   list.currentItem.libName + "'i silmek istediginize emin misiniz ?"
        onAccepted      :   removeSelectedLibrary()
        standardButtons :   Dialog.Yes | Dialog.No
    }

    GenericMessageDialog{
        id              :   installLibraryDialog
        title           :   "Kutuphane yukle"
        message         :   list.currentItem.libName + "'i yuklemek istediginize emin misiniz ?"
        onAccepted      :   installSelectedLibrary()
        standardButtons :   Dialog.Yes | Dialog.No
    }

    InternetAccessibility{
        id              :   internet
        onOnlineChanged :   {
            if(online)
                libManager.retrieveOnlineLibraries();
        }
    }

    ListModel{
        id              :   localLibs
    }

    ListModel{
        id              :   onlineLibs
    }

    Column  {

        anchors.fill    :   parent
        spacing         :   10

        Item{
            id          :   searchControls
            height      :   50
            width       :   mainContainer.width

            GenericTextBox{
                id                  :   nameFilterTxt
                height              :   parent.height
                anchors.left        :   parent.left
                anchors.right       :   installLibButton.left
                anchors.rightMargin :   10
                placeholderText     :   "Kutuphane ara..."
                onTextEdited        :   { filterText = text; filter()}
            }

            GenericButton{
                id                  :   installLibButton
                height              :   parent.height
                width               :   120
                anchors.right       :   parent.right
                text                :   localSearch ? "Sil" : "Yukle"
                onClicked           :   {
                    if(localSearch){
                        removeLibraryDialog.open()
                    }
                    else{
                        installLibraryDialog.open()
                    }
                }
                Behavior on width{
                    SequentialAnimation {
                        ScriptAction    {
                            script      :   installLibButton.visible = true
                        }

                        NumberAnimation {
                            duration    :   200
                        }

                        ScriptAction {
                            script      :   if(localSearch) installLibButton.visible = false
                        }
                    }
                }
            }
        }

        TabBar{
            id                      :   tabBar
            width                   :   mainContainer.width
            onCurrentIndexChanged   :   filter(nameFilterTxt.text)

            background  :   Item{

            }

            GenericTabButton{
                height  :   parent.height
                text    :   "Yuklenenler (" + localLibs.count + ")"
            }

            GenericTabButton{
                height  :   parent.height
                text    :   "Tum Kutuphaneler (" + onlineLibs.count + ")"
            }
        }

        Item{
            width               :   parent.width
            height              :   mainContainer.height - searchControls.height - tabBar.height - 20

            Item{
                anchors.fill    :   parent
                visible         :   !internet.online && !localSearch
                z               :   5

                Text {
                    id                  :   noInternetConnectionText
                    text                :   "Internet baglantinizi kontrol ediniz."
                    anchors.centerIn    :   parent
                    font.pixelSize      :   30
                    color               :   "white"
                }
            }

            ListView    {
                id                  :   list
                model               :   localSearch ? localLibs : onlineLibs
                anchors.fill        :   parent
                clip                :   true
                visible             :   localSearch || internet.online
                focus               :   true

                Keys.onDownPressed  :   list.incrementCurrentIndex()
                Keys.onUpPressed    :   list.decrementCurrentIndex()

                delegate    :   Item{
                    readonly property string libName        :   name
                    readonly property string libVersion     :   version
                    readonly property bool removable        :   isRemovable

                    id                      :   libListItem
                    width                   :   list.width
                    height                  :   60

                    Text {
                        id                  :   tx
                        text                :   name +  " - " + version
                        color               :   "white"
                        font.pixelSize      :   26
                        font.family         :   FontCollection.listItemFont
                        anchors.centerIn    :   parent
                    }

                    Image{
                        id                      :   fixed
                        anchors.left            :   tx.right
                        anchors.leftMargin      :   15
                        anchors.verticalCenter  :   parent.verticalCenter
                        source                  :   "/res/icon/lock-icon.png"
                        fillMode                :   Image.PreserveAspectFit
                        height                  :   parent.height * 0.6
                        visible                 :   !libListItem.removable && localSearch
                        mipmap                  :   true
                    }

                    MouseArea{
                        anchors.fill        :   parent
                        onClicked           :   {
                            list.currentIndex = index
                            list.forceActiveFocus()

                        }
                    }
                }

                highlight               :   Rectangle{   color : "steelblue" }
                highlightMoveDuration   :   300
                Component.onCompleted   :   list.forceActiveFocus()
            }
        }
    }

    GenericProgressBar{
        id                      :   libDownloadProgressBar
        width                   :   200
        height                  :   50
        visible                 :   false
        progress                :   libManager.downloadingProgress
        header                  :   libManager.downloadingLibName
        progressVelocity        :   250
        anchors.bottom          :   parent.bottom
        anchors.bottomMargin    :   10
        anchors.right           :   parent.right
        anchors.rightMargin     :   10
    }
}
