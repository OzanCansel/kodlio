import QtQuick 2.0

SequentialAnimation {

    property Item   animationTarget         :   Item { }
    property int    animDuration            :   1400

    id      :   anim

    onAnimationTargetChanged    :   {
        animationTarget.visible = false
    }

    ScriptAction{
        script      :   {
            animationTarget.opacity = 1
            animationTarget.visible = true
        }
    }

    NumberAnimation{
        target      :   animationTarget
        property    :   "scale"
        from        :   1
        to          :   1.4
        duration    :   animDuration * 0.4
        easing.type :   Easing.OutCirc
    }

    PauseAnimation {
        duration    :   animDuration * 0.35
    }

    NumberAnimation{
        target      :   animationTarget
        property    :   "opacity"
        from        :   1
        to          :   0
        duration    :   animDuration * 0.25
    }

    ScriptAction{
        script      :   {
            animationTarget.opacity = 0
            animationTarget.visible = false
        }
    }
}
