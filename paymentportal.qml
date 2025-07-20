import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    id: root
    width: 400
    height: 600
    visible: true
    color: "#f5f6fa"
    title: "Payment Portal"

    Rectangle {
        anchors.centerIn: parent
        width: 340
        height: 510
        radius: 18
        color: "#ffffff"
        border.color: "#d1d8e0"
        border.width: 1

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 30
            spacing: 16

            // Title
            Label {
                text: "Payment Portal"
                font.pointSize: 21
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                Layout.alignment: Qt.AlignHCenter
                color: "#34495e"
            }

            // User info section
            Frame {
                Layout.fillWidth: true
                background: Rectangle {
                    color: "#f0f2f6"
                    radius: 8
                    border.color: "#d1d8e0"
                }
                ColumnLayout {
                    width: parent.width
                    spacing: 8
                    Label { text: "Name"; font.bold: true }
                    TextField {
                        id: nameField
                        placeholderText: "Your full name"
                        Layout.fillWidth: true
                        background: Rectangle {
                            color: "#ffffff"
                            radius: 5
                            border.color: "#d1d8e0"
                        }
                    }
                    Label { text: "Phone Number"; font.bold: true }
                    TextField {
                        id: phoneField
                        placeholderText: "+977 98XXXXXXXX"
                        inputMethodHints: Qt.ImhDigitsOnly
                        Layout.fillWidth: true
                        background: Rectangle {
                            color: "#ffffff"
                            radius: 5
                            border.color: "#d1d8e0"
                        }
                    }
                }
            }

            // Payment method selector - CORE FIX
            GroupBox {
                title: "Select Payment Method"
                Layout.fillWidth: true
                font.bold: true
                background: Rectangle {
                    color: "#e9ecef"
                    radius: 2
                    border.color: "#d1d8e0"
                }

                ButtonGroup {
                    id: paymentMethodGroup
                    buttons: methodRow.children
                }

                RowLayout {
                    id: methodRow
                    spacing: 20

                    RadioButton {
                        id: esewaBtn
                        checked: true
                        text: "eSewa"
                        font.pointSize: 14
                        indicator: Rectangle {
                            implicitWidth: 20
                            implicitHeight: 20
                            radius: 10
                            border.color: esewaBtn.checked ? "#16a085" : "#95a5a6"
                            Rectangle {
                                anchors.fill: parent
                                visible: esewaBtn.checked
                                color: "#16a085"
                                radius: 10
                                anchors.margins: 4
                            }
                        }
                    }

                    RadioButton {
                        id: khaltiBtn
                        text: "Khalti"
                        font.pointSize: 14
                        indicator: Rectangle {
                            implicitWidth: 20
                            implicitHeight: 20
                            radius: 10
                            border.color: khaltiBtn.checked ? "#5e35b1" : "#95a5a6"
                            Rectangle {
                                anchors.fill: parent
                                visible: khaltiBtn.checked
                                color: "#5e35b1"
                                radius: 10
                                anchors.margins: 4
                            }
                        }
                    }
                }
            }

            // Dynamic form loader
            Loader {
                id: methodLoader
                Layout.fillWidth: true
                Layout.preferredHeight: 120
                sourceComponent: esewaBtn.checked ? esewaForm : khaltiForm
            }

            // Pay button
            Button {
                text: "Pay Now"
                Layout.fillWidth: true
                Layout.preferredHeight: 50
                font.bold: true
                background: Rectangle {
                    color: "#16a085"
                    radius: 8
                }
                contentItem: Text {
                    text: "Pay Now"
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pointSize: 16
                }
                onClicked: paymentHandler.processPayment(
                    nameField.text,
                    phoneField.text,
                    esewaBtn.checked ? "esewa" : "khalti",
                    esewaBtn.checked ? esewaIdField.text : khaltiIdField.text,
                    esewaBtn.checked ? mpinField.text : khaltiPwdField.text
                )
            }
        }
    }

    // --- Form Components ---
    Component {
        id: esewaForm
        ColumnLayout {
            spacing: 8
            Label { text: "eSewa ID"; font.bold: true }
            TextField {
                id: esewaIdField
                placeholderText: "eSewa ID/Email"
                Layout.fillWidth: true
                background: Rectangle {
                    color: "#ffffff"
                    radius: 5
                    border.color: "#d1d8e0"
                }
            }
            Label { text: "MPIN"; font.bold: true }
            TextField {
                id: mpinField
                placeholderText: "Enter MPIN"
                echoMode: TextInput.Password
                Layout.fillWidth: true
                background: Rectangle {
                    color: "#ffffff"
                    radius: 5
                    border.color: "#d1d8e0"
                }
            }
        }
    }

    Component {
        id: khaltiForm
        ColumnLayout {
            spacing: 8
            Label { text: "Khalti Email/Number"; font.bold: true }
            TextField {
                id: khaltiIdField
                placeholderText: "Khalti ID/Phone"
                Layout.fillWidth: true
                background: Rectangle {
                    color: "#ffffff"
                    radius: 5
                    border.color: "#d1d8e0"
                }
            }
            Label { text: "MPIN/Password"; font.bold: true }
            TextField {
                id: khaltiPwdField
                placeholderText: "Enter Password"
                echoMode: TextInput.Password
                Layout.fillWidth: true
                background: Rectangle {
                    color: "#ffffff"
                    radius: 5
                    border.color: "#d1d8e0"

                }
            }
        }
    }
    // Connect signals in QML
    Connections {
        target: paymentHandler
        onValidationFailed: messageDialog.showError(message)
        PaymentProcessed: (name, method) => messageDialog.showSuccess(`Thank you ${name}! Payment via ${method} completed.`)
    }
}
