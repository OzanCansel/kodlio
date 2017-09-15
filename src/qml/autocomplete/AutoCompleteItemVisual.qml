import QtQuick 2.0
import "../singleton"

Item {

    property string     itLabel               :   ""
    property string     itExample             :   ""
    property string     itDescription         :   ""
    property string     itTemplate            :   ""
    property int        itType                :   -1
    property bool       descriptionVisible  :   false

    property int        textWidth           :   0
    property int        descriptionWidth    :   0
    property int        descriptionHeight   :   0

    function        setDescriptionVisible(vis){
        descriptionVisible  =   vis
    }

    Item{
        id              :   textContainer
        anchors.fill    :   parent

        Item{
            id          :   icon
            height      :   parent.height
            width       :   height
            Image   {
                anchors.fill    :   parent
                anchors.margins :   5
                smooth          :   true
                source          :   {
                    if(itType === Enum.method)
                        return "/res/icon/method-icon-40x40.png"
                    else if(itType === Enum.constant)
                        return "/res/icon/constant-40x40.png"
                    else if(itType === Enum.primitiveType)
                        return "/res/icon/primitive-icon-40x40.png"

                }
            }
        }

        Item{
            anchors.left        :   icon.right
            anchors.leftMargin  :   5
            anchors.top         :   parent.top
            anchors.bottom      :   parent.bottom
            anchors.right       :   parent.right
            clip                :   true

            Text {
                id                      :   labelText
                text                    :   itLabel
                font.pointSize          :   9
                anchors.verticalCenter  :   parent.verticalCenter
                anchors.left            :   parent.left
            }
        }
    }

    Rectangle{
        anchors.left        :   textContainer.right
        anchors.leftMargin  :   5
        anchors.top         :   textContainer.top
        height              :   descriptionText.height  +   20
        width               :   descriptionWidth
        visible             :   descriptionVisible
        border.width        :   1
        border.color        :   "#333334"
        radius              :   7
        color               :   Theme.autoCompleteDescriptionColor

        Text {
            id                  :   descriptionText
            anchors.centerIn    :   parent
            text                :   "<span text-indent:\"20px\";><b><font color=\"#0059FF\">   Açıklama</font></b></span><br><p>" + itDescription +   "</p><br> <b><font color=\"#00E100\">Örnek</font></b><br><br><u>"    +   itExample + "</u>"
            font.pointSize      :   10
            width               :   parent.width - 15
            wrapMode            :   Text.WordWrap
            horizontalAlignment :   Text.AlignJustify
            textFormat          :   Text.StyledText
            lineHeight          :   1.3
        }
    }
}
