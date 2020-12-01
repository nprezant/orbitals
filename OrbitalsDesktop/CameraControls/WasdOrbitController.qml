import QtQuick 2.15
import QtQuick3D 1.15

Item {
    id: root
    property Node controlledObject: undefined
    property Node focalObject: undefined

    property real zoomInLimit: 2.0
    property real linearSpeed: 5.0

    Timer {
        id: updateTimer
        interval: 16
        repeat: true
        running: root.inputsNeedProcessing
        onTriggered: {
            processInputs();
        }
    }

    function processInputs()
    {
        if (root.inputsNeedProcessing)
            status.processInput();
    }

    QtObject {
        id: status

        property bool moveForward: false
        property bool moveBack: false
        property bool moveLeft: false
        property bool moveRight: false
        property bool moveUp: false
        property bool moveDown: false
        property bool shiftDown: false
        property bool useMouse: false

        property vector2d lastPos: Qt.vector2d(0, 0)
        property vector2d currentPos: Qt.vector2d(0, 0)

        function updatePosition(vector, speed, position)
        {
            if (shiftDown)
                speed *= shiftSpeed;
            else
                speed *= root.speed

            var direction = vector;
            var velocity = Qt.vector3d(direction.x * speed,
                                       direction.y * speed,
                                       direction.z * speed);
            controlledObject.position = Qt.vector3d(position.x + velocity.x,
                                                    position.y + velocity.y,
                                                    position.z + velocity.z);
        }

        function negate(vector) {
            return Qt.vector3d(-vector.x, -vector.y, -vector.z)
        }

        function clamp(number1, number2)
        {
            var axisValue = number1 + number2;
            return (axisValue < -1) ? -1 : (axisValue > 1) ? 1 : axisValue;
        }

        function processInput() {

            if (controlledObject === undefined || focalObject === undefined)
                return;

            const QVector3D upVector = Qt.vector3d(0.0, 1.0, 0.0);

            // Mouse input
            if (state.leftMouseButtonActive) {
                // Translate
                theCamera->translate(
                    QVector3D(
                        clamp(state.rxAxisValue, state.txAxisValue) * linearSpeed(),
                        clamp(state.ryAxisValue, state.tyAxisValue) * linearSpeed(),
                        0
                    ) * dt);
                return;
            }
            else if (state.rightMouseButtonActive) {
                // Orbit
                theCamera->panAboutViewCenter((state.rxAxisValue * lookSpeed()) * dt, upVector);
                theCamera->tiltAboutViewCenter((state.ryAxisValue * lookSpeed()) * dt);
            }

            // Keyboard Input
            if (state.altKeyActive) {
                // Orbit
                theCamera->panAboutViewCenter((state.txAxisValue * lookSpeed()) * dt, upVector);
                theCamera->tiltAboutViewCenter((state.tyAxisValue * lookSpeed()) * dt);
            } else if (state.shiftKeyActive) {
                if (zoomDistance(camera()->position(), theCamera->viewCenter()) > d->m_zoomInLimit * d->m_zoomInLimit) {
                    // Dolly
                    theCamera->translate(QVector3D(0, 0, state.tzAxisValue * linearSpeed() * dt), theCamera->DontTranslateViewCenter);
                } else {
                    theCamera->translate(QVector3D(0, 0, -0.5), theCamera->DontTranslateViewCenter);
                }
            } else {
                // Translate
                theCamera->translate(QVector3D(clampInputs(state.leftMouseButtonActive ? state.rxAxisValue : 0, state.txAxisValue) * linearSpeed(),
                                            clampInputs(state.leftMouseButtonActive ? state.ryAxisValue : 0, state.tyAxisValue) * linearSpeed(),
                                            state.tzAxisValue * linearSpeed()) * dt);
            }

            // ------------------------------------
            if (moveForward)
                updatePosition(controlledObject.forward, forwardSpeed, controlledObject.position);
            else if (moveBack)
                updatePosition(negate(controlledObject.forward), backSpeed, controlledObject.position);

            if (moveRight)
                updatePosition(controlledObject.right, rightSpeed, controlledObject.position);
            else if (moveLeft)
                updatePosition(negate(controlledObject.right), leftSpeed, controlledObject.position);

            if (moveDown)
                updatePosition(negate(controlledObject.up), downSpeed, controlledObject.position);
            else if (moveUp)
                updatePosition(controlledObject.up, upSpeed, controlledObject.position);

            if (useMouse) {
                // Get the delta
                var rotationVector = controlledObject.eulerRotation;
                var delta = Qt.vector2d(lastPos.x - currentPos.x,
                                        lastPos.y - currentPos.y);
                // rotate x
                var rotateX = delta.x * xSpeed
                if (xInvert)
                    rotateX = -rotateX;
                rotationVector.y += rotateX;

                // rotate y
                var rotateY = delta.y * -ySpeed
                if (yInvert)
                    rotateY = -rotateY;
                rotationVector.x += rotateY;
                controlledObject.setEulerRotation(rotationVector);
                lastPos = currentPos;
            }
        }
    }
}