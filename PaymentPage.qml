import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Effects

Rectangle {
    id: paymentPageRoot
    width: Screen.width
    height: Screen.height

    property bool isEsewa: false
    property bool showEsewaMpin: false
    property bool showKhaltiMpin: false
    property StackView stackView: StackView.view
    property string paymentMessageDialogText: ""

    // Background gradient
    gradient: Gradient {
        GradientStop { position: 0.0; color: "#2c3e50" }
        GradientStop { position: 1.0; color: "#34495e" }
    }

    // Floating elements
    Rectangle {
        anchors.fill: parent
        opacity: 0.04
        Repeater {
            model: 4
            Rectangle {
                width: Math.random() * 80 + 30
                height: width
                radius: width / 2
                color: "#ffffff"
                opacity: 0.3
                x: Math.random() * paymentPageRoot.width
                y: Math.random() * paymentPageRoot.height
                SequentialAnimation on y {
                    running: true; loops: Animation.Infinite
                    NumberAnimation { to: y - 15; duration: 4000; easing.type: Easing.InOutSine }
                    NumberAnimation { to: y + 15; duration: 4000; easing.type: Easing.InOutSine }
                }
            }
        }
    }

    // Payment card
    Rectangle {
        id: card
        width: Math.min(paymentPageRoot.width * 0.92, 1100)
        height: Math.min(paymentPageRoot.height * 0.85, 750)
        anchors.centerIn: parent
        radius: 28
        color: "#40ffffff"
        border.color: "#60ffffff"
        border.width: 2
        scale: 0.88
        opacity: 0

        layer.enabled: true
        layer.effect: MultiEffect {
            shadowEnabled: true
            shadowBlur: 2.0
            shadowColor: "#50000000"
            shadowVerticalOffset: 10
            shadowHorizontalOffset: 0
        }

        Component.onCompleted: entryAnim.start()

        ParallelAnimation {
            id: entryAnim
            NumberAnimation { target: card; property: "scale"; to: 1.0; duration: 550; easing.type: Easing.OutBack }
            NumberAnimation { target: card; property: "opacity"; to: 1.0; duration: 350 }
        }

        // Content form
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 30
            spacing: 20

            Text {
                text: "💳 Complete Your Payment"
                font.pixelSize: 26
                font.bold: true
                color: "#ffffff"
                horizontalAlignment: Text.AlignHCenter
                Layout.alignment: Qt.AlignHCenter
            }
            RowLayout {
                Layout.fillWidth: true
                spacing: 15

                Text {
                    text: "Name:"
                    font.pixelSize: 16
                    color: "#dddddd"
                    Layout.preferredWidth: 130
                    verticalAlignment: Text.AlignVCenter
                }

                TextField {
                    id: nameField
                    placeholderText: "Enter your name"
                    Layout.fillWidth: true
                    font.pixelSize: 16
                    height: 45
                    color: "#ffffff"
                    placeholderTextColor: "#bbbbbb"
                    verticalAlignment: TextInput.AlignVCenter

                    background: Rectangle {
                        radius: 10
                        color: parent.activeFocus ? "#40d0ff20" : "#20ffffff"
                        border.width: 1.2
                        border.color: parent.activeFocus ? "#80d0ff" : "#5080a0"
                        layer.enabled: true
                        layer.effect: MultiEffect {
                            shadowEnabled: parent.activeFocus
                            shadowBlur: 1.8
                            shadowColor: "#40d0ff"
                            shadowVerticalOffset: 2
                        }
                    }
                }
            }

            RowLayout {
                Layout.fillWidth: true
                spacing: 15

                Text {
                    text: "Email:"
                    font.pixelSize: 16
                    color: "#dddddd"
                    Layout.preferredWidth: 130
                    verticalAlignment: Text.AlignVCenter
                }

                TextField {
                    id: emailField
                    placeholderText: "example@email.com"
                    Layout.fillWidth: true
                    font.pixelSize: 16
                    height: 45
                    color: "#ffffff"
                    placeholderTextColor: "#bbbbbb"
                    verticalAlignment: TextInput.AlignVCenter

                    background: Rectangle {
                        radius: 10
                        color: parent.activeFocus ? "#40d0ff20" : "#20ffffff"
                        border.width: 1.2
                        border.color: parent.activeFocus ? "#80d0ff" : "#5080a0"
                        layer.enabled: true
                        layer.effect: MultiEffect {
                            shadowEnabled: parent.activeFocus
                            shadowBlur: 1.8
                            shadowColor: "#40d0ff"
                            shadowVerticalOffset: 2
                        }
                    }
                }
            }

            RowLayout {
                Layout.fillWidth: true
                spacing: 15

                Text {
                    text: "Phone Number:"
                    font.pixelSize: 16
                    color: "#dddddd"
                    Layout.preferredWidth: 130
                    verticalAlignment: Text.AlignVCenter
                }

                TextField {
                    id: phoneField
                    placeholderText: "+977..."
                    Layout.fillWidth: true
                    font.pixelSize: 16
                    height: 45
                    color: "#ffffff"
                    placeholderTextColor: "#bbbbbb"
                    verticalAlignment: TextInput.AlignVCenter

                    background: Rectangle {
                        radius: 10
                        color: parent.activeFocus ? "#40d0ff20" : "#20ffffff"
                        border.width: 1.2
                        border.color: parent.activeFocus ? "#80d0ff" : "#5080a0"
                        layer.enabled: true
                        layer.effect: MultiEffect {
                            shadowEnabled: parent.activeFocus
                            shadowBlur: 1.8
                            shadowColor: "#40d0ff"
                            shadowVerticalOffset: 2
                        }
                    }
                }
            }


            Loader {
                id: paymentForm
                sourceComponent: isEsewa ? esewaForm : khaltiForm
                Layout.fillWidth: true
            }

            // Pay button
            Button {
                id: payBtn
                text: "🧾 Pay Now"
                implicitHeight: 55
                implicitWidth: 200
                Layout.alignment: Qt.AlignHCenter
                scale: hovered ? 1.06 : 1.0

                background: Rectangle {
                    radius: 28
                    gradient: Gradient {
                        GradientStop { position: 0.0; color: payBtn.pressed ? "#27ae60" : "#2ecc71" }
                        GradientStop { position: 1.0; color: payBtn.pressed ? "#229954" : "#27ae60" }
                    }
                    border.color: "#58d68d"
                    border.width: 1

                    layer.enabled: true
                    layer.effect: MultiEffect {
                        shadowEnabled: true
                        shadowBlur: payBtn.hovered ? 1.8 : 1.0
                        shadowColor: payBtn.hovered ? "#2ecc71" : "#27ae60"
                        shadowVerticalOffset: payBtn.hovered ? 8 : 5
                    }
                }

                contentItem: Text {
                    text: payBtn.text
                    font.pixelSize: 18
                    color: "#ffffff"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.weight: Font.Bold
                }

                onClicked: {
                    if (!paymentForm.item) return;
                    const mpin = isEsewa ? paymentForm.item.esewaMpin.text : paymentForm.item.khaltiMpin.text;

                    paymentHandler.processPayment(
                        nameField.text,
                        emailField.text,
                        phoneField.text,
                        isEsewa,
                        mpin
                    );
                }

                Behavior on scale { NumberAnimation { duration: 160; easing.type: Easing.OutQuad } }
            }
        }
    }

    // Dialog
    Dialog {
        id: paymentMessageDialog
        title: "Payment Status"
        standardButtons: Dialog.Ok
        modal: true
        visible: false

        onAccepted: {
            if (title === "Payment Successful") stackView.pop()
        }

        contentItem: Text {
            text: paymentMessageDialogText
            wrapMode: Text.Wrap
            font.pixelSize: 16
        }
    }

    // Forms
    Component {
        id: esewaForm
        ColumnLayout {
            spacing: 10
            Layout.fillWidth: true
            property alias esewaMpin: esewaMpin

            RowLayout {
                spacing: 15
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignVCenter

                Text {
                    text: "MPIN:"
                    font.pixelSize: 16
                    color: "#dddddd"
                    Layout.preferredWidth: 130
                    verticalAlignment: Text.AlignVCenter
                }

                TextField {
                    id: esewaMpin
                    placeholderText: "****"
                    echoMode: showEsewaMpin ? TextInput.Normal : TextInput.Password
                    Layout.fillWidth: true
                    font.pixelSize: 16
                    height: 45
                    color: "#ffffff"
                    placeholderTextColor: "#bbbbbb"
                    verticalAlignment: TextInput.AlignVCenter

                    background: Rectangle {
                        radius: 10
                        color: parent.activeFocus ? "#40d0ff20" : "#20ffffff"
                        border.width: 1.2
                        border.color: parent.activeFocus ? "#80d0ff" : "#5080a0"
                        layer.enabled: true
                        layer.effect: MultiEffect {
                            shadowEnabled: parent.activeFocus
                            shadowBlur: 1.8
                            shadowColor: "#40d0ff"
                            shadowVerticalOffset: 2
                        }
                    }
                }

                Button {
                    id: eyeButton
                    width: 42
                    height: 42
                    padding: 0
                    font.pixelSize: 22
                    text: showEsewaMpin ? "👁️" : "👁️"  // same emoji for now, toggles visibility
                    background: Rectangle {
                        anchors.fill: parent
                        radius: 10
                        color: eyeButton.pressed ? "#40d0ff20" : "#20ffffff"
                        border.width: 1.2
                        border.color: eyeButton.pressed ? "#80d0ff" : "#5080a0"

                        layer.enabled: true
                        layer.effect: MultiEffect {
                            shadowEnabled: eyeButton.hovered || eyeButton.pressed
                            shadowBlur: eyeButton.hovered ? 2 : 1.2
                            shadowColor: "#40d0ff"
                            shadowVerticalOffset: 1.5
                        }
                    }
                    scale: pressed ? 0.9 : (hovered ? 1.05 : 1.0)
                    Behavior on scale { NumberAnimation { duration: 120; easing.type: Easing.OutQuad } }

                    onClicked: showEsewaMpin = !showEsewaMpin
                }
            }
        }
    }

    Component {
        id: khaltiForm
        ColumnLayout {
            spacing: 10
            Layout.fillWidth: true
            property alias khaltiMpin: khaltiMpin

            RowLayout {
                spacing: 15
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignVCenter

                Text {
                    text: "MPIN:"
                    font.pixelSize: 16
                    color: "#dddddd"
                    Layout.preferredWidth: 130
                    verticalAlignment: Text.AlignVCenter
                }

                TextField {
                    id: khaltiMpin
                    placeholderText: "****"
                    echoMode: showKhaltiMpin ? TextInput.Normal : TextInput.Password
                    Layout.fillWidth: true
                    font.pixelSize: 16
                    height: 45
                    color: "#ffffff"
                    placeholderTextColor: "#bbbbbb"
                    verticalAlignment: TextInput.AlignVCenter

                    background: Rectangle {
                        radius: 10
                        color: parent.activeFocus ? "#40d0ff20" : "#20ffffff"
                        border.width: 1.2
                        border.color: parent.activeFocus ? "#80d0ff" : "#5080a0"
                        layer.enabled: true
                        layer.effect: MultiEffect {
                            shadowEnabled: parent.activeFocus
                            shadowBlur: 1.8
                            shadowColor: "#40d0ff"
                            shadowVerticalOffset: 2
                        }
                    }
                }

                Button {
                    id: eyeButton
                    width: 42
                    height: 42
                    padding: 0
                    font.pixelSize: 22
                    text: showKhaltiMpin ? "👁️" : "👁️"
                    background: Rectangle {
                        anchors.fill: parent
                        radius: 10
                        color: eyeButton.pressed ? "#40d0ff20" : "#20ffffff"
                        border.width: 1.2
                        border.color: eyeButton.pressed ? "#80d0ff" : "#5080a0"

                        layer.enabled: true
                        layer.effect: MultiEffect {
                            shadowEnabled: eyeButton.hovered || eyeButton.pressed
                            shadowBlur: eyeButton.hovered ? 2 : 1.2
                            shadowColor: "#40d0ff"
                            shadowVerticalOffset: 1.5
                        }
                    }
                    scale: pressed ? 0.9 : (hovered ? 1.05 : 1.0)
                    Behavior on scale { NumberAnimation { duration: 120; easing.type: Easing.OutQuad } }

                    onClicked: showKhaltiMpin = !showKhaltiMpin
                }
            }
        }
    }

}
