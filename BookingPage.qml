import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    width: Screen.width /2
    height: Screen.height * 0.6
    color: "#e0c3fc"
    radius: 12
    anchors.centerIn: parent

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 30
        spacing: 20

        Text {
            text: "Booking Details"
            font.pixelSize: 24
            font.bold: true
            color: "black"
            horizontalAlignment: Text.AlignHCenter
            Layout.alignment: Qt.AlignHCenter
        }

        // Details grid
        GridLayout {
            columns: 2
            columnSpacing: 20
            rowSpacing: 12
            Layout.alignment: Qt.AlignLeft
            Layout.fillWidth: true

            // Route ID
            Text { text: "Route ID:"; font.pixelSize: 18; color: "black" }
            Text { text: bookingWindow.routeId; font.pixelSize: 18; font.bold: true; color: "black" }

            // From
            Text { text: "From:"; font.pixelSize: 18; color: "black" }
            Text { text: bookingWindow.fromLocation; font.pixelSize: 18; font.bold: true; color: "black" }

            // To
            Text { text: "To:"; font.pixelSize: 18; color: "black" }
            Text { text: bookingWindow.toLocation; font.pixelSize: 18; font.bold: true; color: "black" }

            // Departure - Arrival time
            Text { text: "Time:"; font.pixelSize: 18; color: "black" }
            Text { text: bookingWindow.departureTime + " - " + bookingWindow.arrivalTime; font.pixelSize: 18; font.bold: true; color: "black" }

            // Price
            Text { text: "Price:"; font.pixelSize: 18; color: "black" }
            Text { text: "Rs. " + bookingWindow.ticketPrice; font.pixelSize: 18; font.bold: true; color: "black" }

            // Bus No.
            Text { text: "Bus No.:"; font.pixelSize: 18; color: "black" }
            Text { text: bookingWindow.busNo; font.pixelSize: 18; font.bold: true; color: "black" }

            // Driver
            Text { text: "Driver:"; font.pixelSize: 18; color: "black" }
            Text { text: bookingWindow.driverInfo; font.pixelSize: 18; font.bold: true; color: "black" }

            // Contact
            Text { text: "Contact:"; font.pixelSize: 18; color: "black" }
            Text { text: bookingWindow.contactPhone; font.pixelSize: 18; font.bold: true; color: "black" }

            // Seats
            Text { text: "Seats:"; font.pixelSize: 18; color: "black" }
            Text { text: bookingWindow.seatNo; font.pixelSize: 18; font.bold: true; color: "black" }
        }

        // Buttons at bottom
        RowLayout {
            spacing: 40
            Layout.alignment: Qt.AlignHCenter
            Layout.fillWidth: true

            Button {
                text: "Pay Now"
                width: 100
                height: 30
                onClicked: bookingWindow.initiatePayment()
            }
        }
    }
}
