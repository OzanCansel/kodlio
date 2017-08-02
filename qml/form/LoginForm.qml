import QtQuick 2.0
import QtQuick.Controls 2.1
import Kodlio 1.0
import "../singleton"
import "../control"

FocusScope {

    property Cloud      cloud   :   ({})

    function    clear(){
        userNameField.clear()
        passwordField.clear()
    }

    width               :   400
    height              :   200

    Image {
        id          :   img
        source      :   "/res/icon/backgroundpattern.png"
        anchors.fill:   parent
        fillMode    :   Image.Tile
        z           :   0
    }

    readonly property string    userName    :   userNameField.text
    readonly property string    password    :   passwordField.text

    function    login(){
        var res = cloud.authenticate(userName , password)

        if(res){
            Global.displayMessage(userName + " hoşgeldin.")
        }else{
            Global.displayMessage("Kullanıcı adı veya şifre hatalı ")
        }
    }

    Keys.onEnterPressed :   login()
    Keys.onReturnPressed:   login()

    Column  {
        anchors.fill    :   parent
        anchors.margins :   15
        spacing         :   10

        Row {
            id      :   userNameRow
            width   :   parent.width
            height  :   50
            spacing :   10

            Image {
                id          :   usernameIcon
                source      :   "/res/icon/username.png"
                height      :   parent.height
                fillMode    :   Image.PreserveAspectFit
            }

            GenericTextBox{
                id      :   userNameField
                width   :   parent.width - usernameIcon.width - userNameRow.spacing
                height  :   50
                anchors.verticalCenter  :   parent.verticalCenter
                placeholderText :   "Kullanıcı adı."
                backgroundRect.border.width :   0
                backgroundRect.radius       :   0
            }
        }

        Row{
            id      :   passwordRow
            width   :   parent.width
            height  :   50
            spacing :   10

            Image {
                id      :   passwordIcon
                source  :   "/res/icon/password.png"
                height  :   parent.height
                fillMode    :   Image.PreserveAspectFit
            }

            GenericTextBox{
                id                          :   passwordField
                width                       :   parent.width - passwordIcon.width - passwordRow.spacing
                height                      :   50
                placeholderText             :   "Şifre giriniz..."
                backgroundRect.border.width :   0
                backgroundRect.radius       :   0
                echoMode                    :   TextInput.Password
            }
        }

        GenericButton{
            id                          :   loginButton
            width                       :   160
            height                      :   40
            text                        :   "Giriş"
            anchors.right               :   parent.right
            anchors.rightMargin         :   5
            backgroundRect.radius       :   0
            backgroundRect.color        :   "#fe7902"
            backgroundRect.border.width :   0
            onClicked                   :   login()
        }
    }
}
