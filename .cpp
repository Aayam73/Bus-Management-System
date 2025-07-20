#include &lt;QApplication&gt;
#include &lt;QMainWindow&gt;
#include &lt;QWidget&gt;
#include &lt;QVBoxLayout&gt;
#include &lt;QHBoxLayout&gt;
#include &lt;QLabel&gt;
#include &lt;QLineEdit&gt;
#include &lt;QTimeEdit&gt;
#include &lt;QTableView&gt;
#include &lt;QHeaderView&gt;

class MainWindow : public QMainWindow {
public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("Bus Search UI");

        QWidget *central = new QWidget(this);
        setCentralWidget(central);

        QVBoxLayout *mainLayout = new QVBoxLayout(central);

        // Filter inputs horizontal layout
        QHBoxLayout *filtersLayout = new QHBoxLayout();

        QLabel *startLabel = new QLabel("Start Destination:");
        QLineEdit *startEdit = new QLineEdit();
        startEdit->setPlaceholderText("Enter start destination");

        QLabel *endLabel = new QLabel("End Destination:");
        QLineEdit *endEdit = new QLineEdit();
        endEdit->setPlaceholderText("Enter end destination");

        QLabel *timeLabel = new QLabel("Departure Time (from):");
        QTimeEdit *timeEdit = new QTimeEdit();
        timeEdit->setDisplayFormat("HH:mm");
        timeEdit->setTime(QTime(0,0));
        timeEdit->setMinimumTime(QTime(0,0));
        timeEdit->setMaximumTime(QTime(23,59));
        timeEdit->setMinimumWidth(100);

        filtersLayout->addWidget(startLabel);
        filtersLayout->addWidget(startEdit);
        filtersLayout->addSpacing(10);
        filtersLayout->addWidget(endLabel);
        filtersLayout->addWidget(endEdit);
        filtersLayout->addSpacing(10);
        filtersLayout->addWidget(timeLabel);
        filtersLayout->addWidget(timeEdit);

        mainLayout->addLayout(filtersLayout);

        // Table view placeholder for showing results
        QTableView *tableView = new QTableView();
        tableView->setEditTriggers(QTableView::NoEditTriggers);
        tableView->setSelectionBehavior(QTableView::SelectRows);
        tableView->horizontalHeader()->setStretchLastSection(true);
        tableView->setMinimumHeight(400);

        mainLayout->addWidget(tableView);
    }
};

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(900, 500);
    w.show();
    return a.exec();
}

