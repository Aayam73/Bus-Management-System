import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs

ApplicationWindow {
    id: reservationWindow
    width: 440
    height: 680
    visible: true
    title: qsTr("Reservation Confirmed")

    // Booking Properties
    property string fullName: "Anwesh Humagain"
    property string phoneNumber: "9801234567"
    property string method: "eSewa"
    property string fromLocation: "Kathmandu"
    property string toLocation: "Pokhara"
     property string seatNumber: "A1"
    property date travelDate: new Date(2025, 7, 25)
    property date reservationDate: new Date()

    ToolBar {
        id: header
        anchors.top: parent.top
        width: parent.width

        RowLayout {
            anchors.fill: parent
            spacing: 10

            ToolButton {
                icon.name: "check_circle"
                enabled: false
            }

            Label {
                text: qsTr("Reservation Confirmed")
                font.pixelSize: 20
                Layout.alignment: Qt.AlignVCenter
            }
        }
    }

    Flickable {
        id: flick
        anchors.top: header.bottom
        anchors.bottom: footer.top
        anchors.left: parent.left
        anchors.right: parent.right
        clip: true
        contentWidth: flick.width
        contentHeight: columnContainer.implicitHeight

        Item {
            id: columnContainer
            width: flick.width
            height: column.implicitHeight

            ColumnLayout {
                id: column
                width: flick.width
                spacing: 16
                anchors.margins: 16

                GroupBox {
                    title: qsTr("Passenger")
                    Layout.fillWidth: true

                    GridLayout {
                        columns: 2
                        rowSpacing: 8
                        columnSpacing: 12
                        anchors.margins: 10

                        Label { text: qsTr("Name:") }
                        Label { text: fullName }

                        Label { text: qsTr("Phone:") }
                        Label { text: phoneNumber }

                        Label { text: qsTr("Payment Method:") }
                        Label { text: method }
                    }
                }

                GroupBox {
                    title: qsTr("Trip Details")
                    Layout.fillWidth: true

                    GridLayout {
                        columns: 2
                        rowSpacing: 8
                        columnSpacing: 12
                        anchors.margins: 10

                        Label { text: qsTr("From:") }
                        Label { text: fromLocation }

                        Label { text: qsTr("To:") }
                        Label { text: toLocation }

                        Label { text: qsTr("Travel Date:") }
                        Label { text: Qt.formatDate(travelDate, "dd MMM yyyy") }

                        Label { text: qsTr("Reservation Made On:") }
                        Label { text: Qt.formatDateTime(reservationDate, "dd MMM yyyy hh:mm") }

                        Label { text: qsTr("Seat Number::") }
                        Label { text: seatNumber }
                    }
                }

                Label {
                    text: qsTr("Please download your ticket. Bookings auto-expire 24 hours after reservation.")
                    wrapMode: Text.WordWrap
                    Layout.fillWidth: true
                    padding: 8
                    color: "#666"
                }
            }
        }
    }

    ToolBar {
        id: footer
        anchors.bottom: parent.bottom
        width: parent.width
        height: 60

        RowLayout {
            anchors.fill: parent
            spacing: 10
            anchors.margins: 10

            Item { Layout.fillWidth: true }

            Button {
                text: qsTr("Download PDF")
                icon.name: "download"
                font.bold: true
                background: Rectangle {
                    color: "#009688"
                    radius: 6
                }
                contentItem: Text {
                    text: qsTr("Download PDF")
                    color: "white"
                    font.bold: true
                    anchors.centerIn: parent
                }
                onClicked: {
                    reservationHandler.exportToPDF(
                                fullName,
                                    fromLocation + " → " + toLocation,
                                    Qt.formatDate(travelDate, "dd MMM yyyy"),
                                    seatNumber,
                                    phoneNumber
                    )
                    messageDialog.text = "PDF downloaded successfully!"
                    messageDialog.open()
                }
            }

            Button {
                text: qsTr("Done")
                icon.name: "check"
                highlighted: true
                onClicked: reservationWindow.close()
            }
        }
    }

    MessageDialog {
        id: messageDialog
        title: "Download"
        text: "PDF downloaded successfully!"
        visible: false
    }

    Component.onCompleted: {
        console.log("DEBUG FULL NAME:", fullName)
    }
}
