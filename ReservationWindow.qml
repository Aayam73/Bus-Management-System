import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs

Rectangle {
    id: reservationWindow
    width: 440
    height: 680
    visible: true

    // Booking Properties
    property string fullName: ""
    property string phoneNumber: ""
    property string method: ""
    property string fromLocation: ""
    property string toLocation: ""
    property string departureTime: ""
    property string arrivalTime: ""
    property string ticketPrice: ""
    property string busNo: ""
    property string driverInfo: ""
    property string contactPhone: ""
    property date date: new Date()
    property date reservationDate: new Date()
    property string routeId: ""
    property bool isEsewa: false
    property bool showEsewaMpin: false
    property bool showKhaltiMpin: false

    Rectangle {
        id: titleBar
        width: parent.width
        height: 40
        color: "#2c3e50"

        Text {
            text: "Reservation Confirmed"
            anchors.centerIn: parent
            color: "white"
            font.bold: true
            font.pointSize: 16
        }
    }

    // Debug connections
    Connections {
        target: reservationWindow
        function onFullNameChanged() { console.log("Updated:", fullName) }
        function onPhoneNumberChanged() { console.log("Updated:", phoneNumber) }
        function onMethodChanged() { console.log("Updated:", method) }
        function onFromLocationChanged() { console.log("Updated:", fromLocation) }
        function onToLocationChanged() { console.log("Updated:", toLocation) }
        function onDepartureTimeChanged() { console.log("Updated:", departureTime) }
        function onArrivalTimeChanged() { console.log("Updated:", arrivalTime) }
        function onTicketPriceChanged() { console.log("Updated:", ticketPrice) }
        function onBusNoChanged() { console.log("Updated:", busNo) }
        function onDriverInfoChanged() { console.log("Updated:", driverInfo) }
        function onContactPhoneChanged() { console.log("Updated:", contactPhone) }
        function onDateChanged() { console.log("Updated:", date) }
        function onReservationDateChanged() { console.log("Updated:", reservationDate) }
        function onRouteIdChanged() { console.log("Updated:", routeId) }
    }

    ToolBar {
        id: header
        anchors.top: parent.top
        width: parent.width
        height: 60

        RowLayout {
            anchors.fill: parent
            spacing: 10

            Label {
                text: qsTr("Reservation Confirmed")
                font.pixelSize: 20
                font.bold: true
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
        contentHeight: columnContainer.implicitHeight + (column.anchors.margins * 2)

        Item {
            id: columnContainer
            width: flick.width
            implicitHeight: column.implicitHeight + (column.anchors.margins * 2)

            ColumnLayout {
                id: column
                width: parent.width
                spacing: 16
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.margins: 16

                RowLayout {
                                id: logoRow
                                Layout.fillWidth: true
                                spacing: 10
                                Layout.alignment: Qt.AlignHCenter

                                Text {
                                    text: qsTr("Hamro Bus Sewa")
                                    font.bold: true
                                    font.pixelSize: 20
                                    color: "#2c3e50"
                                    verticalAlignment: Text.AlignVCenter
                                }
                            }

                // Passenger Details
                GroupBox {
                    title: qsTr("Passenger Details")
                    Layout.fillWidth: true
                    background: Rectangle {
                        color: "white"
                        radius: 5
                        border.color: "#ddd"
                        border.width: 1
                    }

                    GridLayout {
                        columns: 2
                        rowSpacing: 8
                        columnSpacing: 16
                        anchors.fill: parent
                        anchors.margins: 10

                        Label { text: qsTr("Full Name:"); font.bold: true; color: "black"}
                        Label { text: reservationWindow.fullName; font.pixelSize: 15; color: "#333" }

                        Label { text: qsTr("Phone Number:"); font.bold: true; color: "black" }
                        Label { text: reservationWindow.phoneNumber; font.pixelSize: 15; color: "#333" }

                        Label { text: qsTr("Payment Method:"); font.bold: true; color: "black" }
                        Label { text: reservationWindow.method; font.pixelSize: 15; color: "#333" }
                    }

                }

                GroupBox {
                    title: qsTr("QR Code")
                    Layout.fillWidth: true
                    background: Rectangle {
                        color: "white"
                        radius: 5
                        border.color: "#ddd"
                        border.width: 1
                    }

                    Image {
                        id: qrImage
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        width: 150
                        height: 150
                        fillMode: Image.PreserveAspectFit
                    }

                    Component.onCompleted: {
                        // Generate QR using reservation data
                        var qrData = fullName + "|" + fromLocation + " → " + toLocation + "|" + date
                        var path = reservationHandler.generateQRCode(qrData)
                        qrImage.source = "file:///" + path
                    }
                }


                // Trip Information
                GroupBox {
                    title: qsTr("Trip Information")
                    Layout.fillWidth: true
                    background: Rectangle {
                        color: "white"
                        radius: 5
                        border.color: "#ddd"
                        border.width: 1
                    }

                    GridLayout {
                        columns: 2
                        rowSpacing: 8
                        columnSpacing: 16
                        anchors.fill: parent
                        anchors.margins: 10

                        Label { text: qsTr("Route:"); font.bold: true; color: "black"}
                        Label { text: fromLocation + " → " + toLocation; font.pixelSize: 15; color: "#333" }

                        Label { text: qsTr("Departure Time:"); font.bold: true; color: "black" }
                        Label { text: departureTime; font.pixelSize: 15; color: "#333" }

                        Label { text: qsTr("Arrival Time:"); font.bold: true; color: "black" }
                        Label { text: arrivalTime; font.pixelSize: 15; color: "#333" }

                        Label { text: qsTr("Bus Number:"); font.bold: true; color: "black" }
                        Label { text: busNo; font.pixelSize: 15; color: "#333" }

                        Label { text: qsTr("Driver Name:"); font.bold: true; color: "black" }
                        Label { text: driverInfo; font.pixelSize: 15; color: "#333" }

                        Label { text: qsTr("Driver Contact:"); font.bold: true; color: "black" }
                        Label { text: contactPhone; font.pixelSize: 15; color: "#333" }

                        Label { text: qsTr("Ticket Price:"); font.bold: true; color: "black" }
                        Label {
                            text: {
                                var priceNum = parseFloat(ticketPrice)
                                return isNaN(priceNum) ? "Rs. 0.00" : "Rs. " + priceNum.toFixed(2)
                            }
                            font.pixelSize: 15; color: "#333"
                        }

                        Label { text: qsTr("Travel Date:"); font.bold: true; color: "black" }
                        Label { text: Qt.formatDate(date, "dd MMM yyyy"); font.pixelSize: 15; color: "#333" }

                        Label { text: qsTr("Reservation Made On:"); font.bold: true; color: "black" }
                        Label { text: Qt.formatDateTime(reservationDate, "dd MMM yyyy hh:mm"); font.pixelSize: 15; color: "#333" }
                    }
                }

                Label {
                    text: qsTr("Please download your ticket. Bookings auto-expire 24 hours after reservation.")
                    wrapMode: Text.WordWrap
                    Layout.fillWidth: true
                    padding: 8
                    color: "#666"
                    font.pixelSize: 13
                    horizontalAlignment: Text.AlignHCenter
                    Layout.topMargin: 10
                    Layout.bottomMargin: 10
                }
            }
        }
    }

    ToolBar {
        id: footer
        anchors.bottom: parent.bottom
        width: parent.width
        height: 60
        spacing: 10

        RowLayout {
            anchors.fill: parent
            spacing: 10
            anchors.margins: 10

            Item { Layout.fillWidth: true }

            Button {
                id: downloadPdfButton
                text: qsTr("Download PDF")
                font.bold: true
                enabled: true

                background: Rectangle {
                    color: downloadPdfButton.enabled ? "#009688" : "#A0A0A0"
                    radius: 6
                }
                contentItem: Text {
                    text: parent.text
                    color: downloadPdfButton.enabled ? "white" : "#E0E0E0"
                    font.bold: true
                    anchors.centerIn: parent
                }

                onClicked: {
                    downloadPdfButton.enabled = false
                    reservationHandler.exportToPDF(
                        fullName,
                        fromLocation + " → " + toLocation,
                        Qt.formatDate(date, "dd MMM yyyy"),
                        phoneNumber,
                        departureTime,
                        arrivalTime,
                        busNo,
                        driverInfo,
                        contactPhone,
                        parseFloat(ticketPrice).toFixed(2),
                        method,
                        Qt.formatDateTime(reservationDate, "dd MMM yyyy hh:mm")
                        )
                    messageDialog.text = qsTr("PDF downloaded successfully!")
                    messageDialog.open()
                    downloadPdfButton.enabled = true
                }
            }

            Button {
                text: qsTr("Done")
                highlighted: true
                onClicked: reservationHandler.close()
            }
        }
    }

    MessageDialog {
        id: messageDialog
        title: "Download"
        text: "PDF downloaded successfully!"
        visible: false
    }
}
