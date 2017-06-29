import QtQuick 2.0
import Roboskop 1.0
import "../control"

Item {

    implicitWidth   :   500
    implicitHeight  :   600

    property    variant     sections    :   []
    signal  closeMe()

    ListModel{
        id      :   examplesModel
    }

    ListModel{
        id      :   filteredModel
    }

    function    refresh(){
        var examples =  traverse.readProjects(environment.appDirPath() + "/examples" , "")
        examplesModel.clear()
        filteredModel.clear()

        for(var cat in examples ){
            if(cat === "isCategory")    continue;
            var     example = examples[cat]
            for(var lesson in example){
                if(lesson === "isCategory") continue;
                var item = { "name" : lesson , "category" : cat , "path" : example[lesson]["path"]};
                examplesModel.append(item);
                filteredModel.append(item);
            }
        }

        filter(filterTxtBox.text)
    }

    function    openExample(){
        projectManager.openProject(examplesList.currentItem.examplePath)
        projectManager.readOnly = true
        closeMe()
    }

    function    sectionContains(sectName){

        for(var i = 0; i < sections.length; i++){
            if(sections[i].section === sectName)
                return true
        }

        return false
    }

    function    filter(name){
//        for(var i = 0; i < examplesList.count; i++){
//            var del = examplesList.contentItem.children[i];
//            if(del.exampleName && del.exampleName === name){
//                examplesList.positionViewAtIndex(i, ListView.Center)
//                examplesList.currentIndex = i;
//            }
//        }
        filteredModel.clear()
        for(var i = 0; i < examplesModel.count; i++){
            var item = examplesModel.get(i);
            if(item.name.indexOf(name) !== -1){
                filteredModel.append(item)
            }
        }
    }

    ProjectTraverse{
        id      :   traverse
    }

    Component{

        id      :   exampleDelegate

        Item{
            property string     examplePath :   path
            property string     exampleName :   name
            id                  :   exDel
            width               :   parent.width
            implicitHeight      :   50

            Text {
                id                  :   exampleDescription
                text                :   exDel.exampleName
                font.pointSize      :   12
                color               :   "white"
                anchors.centerIn    :   parent
            }

            MouseArea{
                anchors.fill        :   parent
                onClicked           :   examplesList.currentIndex = index
                onDoubleClicked     :   openExample()
            }
        }
    }

    Component   {
        id              :   sectionDelegate

        Item{
            height      :   60
            width       :   parent.width

            Text {
                id                  :   sectionHeader
                text                :   section
                anchors.centerIn    :   parent
                color               :   "white"
                font.pixelSize      :   30
                font.bold           :   true
                z                   :   2
            }


            Rectangle{
                id                  :   back
                anchors.fill        :   parent
                color               :   "#075688"
                opacity             :   0.6
            }
        }
    }

    ListView{
        id                  :   examplesList
        model               :   filteredModel
        delegate            :   exampleDelegate
        width               :   parent.width
        anchors.top         :   controlBar.bottom
        anchors.topMargin   :   20
        anchors.bottom      :   parent.bottom
        highlight           :   Rectangle{   color : "steelblue" }
        section.criteria    :   ViewSection.FullString
        section.delegate    :   sectionDelegate
        section.property    :   "category"
        clip                :   true
        NumberAnimation { properties: "x,y"; duration: 400; easing.type: Easing.OutBounce }
    }

    Item{
        id                  :   controlBar
        anchors.top         :   parent.top
        height              :   60
        width               :   parent.width

        Row {
            anchors.fill    :   parent
            spacing         :   10
            GenericTextBox{
                id          :   filterTxtBox
                width       :   parent.width - (openExampleButton.width) - (parent.spacing)
                height      :   parent.height
                onTextChanged   :   filter(text)
            }
            GenericButton{
                id          :   openExampleButton
                text        :   "Aç"
                width       :   120
                height      :   parent.height
                onClicked   :   openExample()
            }
        }
    }
}
