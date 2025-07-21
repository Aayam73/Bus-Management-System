// PaymentPortal.qml
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs 1.2

Rectangle {
    id: paymentPageRoot
        width: Screen.width
        height: Screen.height

    property bool isEsewa: false
    property bool showEsewaMpin: false
    property bool showKhaltiMpin: false

        MessageDialog {
                id: paymentMessageDialog
                title: "Payment Status"
                text: ""
                standardButtons: StandardButton.Ok
                onAccepted: {
                    if (paymentMessageDialog.title === "Payment Successful") {
                        stackView.pop(); // Go back to the previous page on success
                    }
                }
            }

        Connections {
                target: paymentHandler // This must match the context property name in main.cpp

                function onPaymentSuccess(message) {
                    console.log("QML: Payment success received:", message);
                    paymentMessageDialog.title = "Payment Successful";
                    paymentMessageDialog.text = message;
                    paymentMessageDialog.visible = true; // Show the success dialog
                }

                function onPaymentFailed(errorMessage) {
                    console.log("QML: Payment failed received:", errorMessage);
                    paymentMessageDialog.title = "Payment Failed";
                    paymentMessageDialog.text = errorMessage;
                    paymentMessageDialog.visible = true;
                }

                function onValidationError(fieldName, errorMessage) {
                    console.log("QML: Validation error on '" + fieldName + "':", errorMessage);
                    paymentMessageDialog.title = "Input Error";
                    paymentMessageDialog.text = errorMessage;
                    paymentMessageDialog.visible = true;

                    // Optional: set focus to the erroneous field
                    // More robust way to focus fields inside a Loader
                    if (fieldName === "nameField") nameField.forceActiveFocus();
                    else if (fieldName === "emailField") emailField.forceActiveFocus();
                    else if (fieldName === "phoneField") phoneField.forceActiveFocus();
                    else if (paymentForm.item) { // Check if the loader has an item loaded
                        if (fieldName === "esewaId" && isEsewa) paymentForm.item.esewaId.forceActiveFocus();
                        else if (fieldName === "esewaMpin" && isEsewa) paymentForm.item.esewaMpin.forceActiveFocus();
                        else if (fieldName === "khaltiId" && !isEsewa) paymentForm.item.khaltiId.forceActiveFocus();
                        else if (fieldName === "khaltiMpin" && !isEsewa) paymentForm.item.khaltiMpin.forceActiveFocus();
                    }
                }
            }

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 16
        width: parent.width * 1

        TextField {
            id: nameField
            placeholderText: "Enter valid name"
        }

        TextField {
            id: emailField
            placeholderText: "example@gmail.com"
        }

        TextField {
            id: phoneField
            placeholderText: "Phone no eg:+977....."
        }

        RowLayout {
            spacing: 20
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

        // Payment form section
        Loader {
            id: paymentForm
            sourceComponent: isEsewa ? esewaForm : khaltiForm
        }

        Button {
            text: "PAY"
            onClicked: {
                paymentHandler.processPayment(
                    nameField.text,
                    emailField.text,
                    phoneField.text,
                    isEsewa,
                    isEsewa ? esewaId.text : khaltiId.text,
                    isEsewa ? esewaMpin.text : khaltiMpin.text
                )
            }
        }

        Button {
                    text: "Back"
                    Layout.fillWidth: true
                    onClicked: {
                        stackView.pop(); // Pop this page from the stack
                    }
            }
    }



    Component {
        id: esewaForm
        ColumnLayout {
            spacing: 10
            TextField {
                id: esewaId
                placeholderText: "eSewa ID/Phone no"
            }
            RowLayout {
                spacing: 5
                TextField {
                    id: esewaMpin
                    placeholderText: "MPIN"
                    echoMode: showEsewaMpin ? TextInput.Normal : TextInput.Password
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
            TextField {
                id: khaltiId
                placeholderText: "Khalti ID/Phone no"
            }
            RowLayout {
                spacing: 5
                TextField {
                    id: khaltiMpin
                    placeholderText: "MPIN"
                    echoMode: showKhaltiMpin ? TextInput.Normal : TextInput.Password
                }
                Button {
                    text: "👁️"
                    onClicked: showKhaltiMpin = !showKhaltiMpin
                }
            }
        }
    }
}
