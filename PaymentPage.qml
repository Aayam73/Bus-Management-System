import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: paymentPageRoot
    width: Screen.width / 2
    height: Screen.height / 2
    color: "#e0c3fc"
    gradient: Gradient {
        GradientStop { position: 0.0; color: "#8ec5fc" }
        GradientStop { position: 1.0; color: "#e0c3fc" }
    }

    property bool isEsewa: false
    property bool showEsewaMpin: false
    property bool showKhaltiMpin: false

    property StackView stackView: StackView.view

    Dialog {
        id: paymentMessageDialog
        title: "Payment Status"
        standardButtons: Dialog.Ok
        modal: true
        visible: false

        onAccepted: {
            if (paymentMessageDialog.title === "Payment Successful") {
                stackView.pop()
            }
        }

        contentItem: Text {
            text: paymentMessageDialogText
            wrapMode: Text.Wrap
        }
    }
    property string paymentMessageDialogText: ""

    Connections {
        target: paymentHandler
    }

    Item {
        id: contentContainer
        anchors.centerIn: parent
        width: parent.width * 0.8
        height: parent.height * 0.85

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 40
            spacing: 20

            TextField {
                id: nameField
                placeholderText: "Enter valid name"
                Layout.fillWidth: true
            }

            TextField {
                id: emailField
                placeholderText: "example@gmail.com"
                Layout.fillWidth: true
            }

            TextField {
                id: phoneField
                placeholderText: "Phone no eg:+977....."
                Layout.fillWidth: true
            }

            RowLayout {
                spacing: 20
                Layout.alignment: Qt.AlignHCenter

                RadioButton {
                    id: radioKhalti
                    text: "Khalti"
                    onClicked: isEsewa = false
                }

                RadioButton {
                    id: radioEsewa
                    text: "eSewa"
                    onClicked: isEsewa = true
                }
            }

            Loader {
                id: paymentForm
                sourceComponent: isEsewa ? esewaForm : khaltiForm
                Layout.fillWidth: true
            }

            Button {
                text: "PAY"
                Layout.fillWidth: true
                onClicked: {
                    if (!paymentForm.item)
                        return;

                    const mpinText = isEsewa ? paymentForm.item.esewaMpin.text : paymentForm.item.khaltiMpin.text;

                    paymentHandler.processPayment(
                        nameField.text,
                        emailField.text,
                        phoneField.text,
                        isEsewa,
                        mpinText
                    );
                }
            }
        }
    }

    // Components must be siblings of Item, not inside it!

    Component {
        id: esewaForm
        ColumnLayout {
            spacing: 10
            Layout.fillWidth: true

            property alias esewaMpin: esewaMpin

            RowLayout {
                spacing: 5
                Layout.fillWidth: true

                TextField {
                    id: esewaMpin
                    placeholderText: "MPIN"
                    echoMode: showEsewaMpin ? TextInput.Normal : TextInput.Password
                    Layout.fillWidth: true
                }

                Button {
                    text: "👁️"
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
                spacing: 5
                Layout.fillWidth: true

                TextField {
                    id: khaltiMpin
                    placeholderText: "MPIN"
                    echoMode: showKhaltiMpin ? TextInput.Normal : TextInput.Password
                    Layout.fillWidth: true
                }

                Button {
                    text: "👁️"
                    onClicked: showKhaltiMpin = !showKhaltiMpin
                }
            }
        }
    }
}
