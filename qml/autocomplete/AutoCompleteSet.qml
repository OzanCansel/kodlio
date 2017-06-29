import QtQuick 2.0

ListModel {

//    property ListModel labels   :   ListModel   {   }

    function    reindex(start){
        for(var i = 0; i < count; i++){
            get(i).itemId = i
            start++
        }
    }
    function    getByKey(key){
        for(var i = 0; i < count; i++){
            if(get(i).itemId === key)
                return get(i)
        }
    }

    function    appendItem(item){
        append(item)
    }

}
