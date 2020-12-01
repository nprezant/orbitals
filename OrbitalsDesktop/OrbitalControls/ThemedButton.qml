import QtQuick 2.15
import QtQuick.Controls 2.14

import Theme 1.0

Button {
    background: Rectangle {
        opacity: enabled ? 1 : 0.3
        color: parent.down ? Theme.bgColorDarkened : Theme.bgColor
        border.color: Theme.borderColor
        radius: Theme.borderRadius
    }
}