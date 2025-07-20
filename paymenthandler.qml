// PaymentPortal.qml
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    visible: true
    width: 1200
    height: 800
    title: "PaymentPortal"

    property bool isEsewa: false
    property bool showEsewaMpin: false
    property bool showKhaltiMpin: false

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

