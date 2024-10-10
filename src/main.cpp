#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QString>
#include <QPushButton>
#include <QStackedWidget>
#include <QSplitter>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <scnt-puq/systems/systems.h>

class MainWindow : public QMainWindow {
public:
    MainWindow() {
        // Central widget for the main window
        QWidget *centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);

        // Create a vertical layout for the central widget
        QVBoxLayout *layout = new QVBoxLayout(centralWidget);

        // Create a splitter to divide the left buttons and the right content
        QSplitter *splitter = new QSplitter(Qt::Horizontal, this);

        // Left panel (Vertical layout for buttons)
        QWidget *buttonPanel = new QWidget();
        QVBoxLayout *buttonLayout = new QVBoxLayout(buttonPanel);
        
        // Buttons for sections
        QPushButton *section1Button = new QPushButton("Conversions", this);
        QPushButton *section2Button = new QPushButton("Calculator", this);
        QPushButton *section3Button = new QPushButton("Unit systems", this);
        
        // Add buttons to the layout
        buttonLayout->addWidget(section1Button);
        buttonLayout->addWidget(section2Button);
        buttonLayout->addWidget(section3Button);
        buttonLayout->addStretch(); // Push buttons to the top

        // Right panel (QStackedWidget to switch between section contents)
        QStackedWidget *stackedWidget = new QStackedWidget();

        // --- Section 1: Simple Text Input ---
        QWidget *section1 = new QWidget();
        QVBoxLayout *section1Layout = new QVBoxLayout(section1);
	section1Layout->setAlignment(Qt::AlignTop);
        QComboBox *selectBox1 = new QComboBox(section1);
	for (auto sys: puq::SystemMap) {
	  QString str = QString::fromStdString(sys.second->SystemAbbrev+" - "+sys.second->SystemName);
	  selectBox1->addItem(str);
	}
        section1Layout->addWidget(selectBox1);
        QLineEdit *simpleTextInput = new QLineEdit(section1);
        section1Layout->addWidget(simpleTextInput);
        
        // --- Section 2: Multi-line Text Input ---
        QWidget *section2 = new QWidget();
        QVBoxLayout *section2Layout = new QVBoxLayout(section2);
	section2Layout->setAlignment(Qt::AlignTop);
        QTextEdit *multiLineInput = new QTextEdit(section2);
        section2Layout->addWidget(multiLineInput);

        // --- Section 3: Select Box ---
        QWidget *section3 = new QWidget();
        QVBoxLayout *section3Layout = new QVBoxLayout(section3);
	section3Layout->setAlignment(Qt::AlignTop);
        QComboBox *selectBox = new QComboBox(section3);
        selectBox->addItem("Option 1");
        selectBox->addItem("Option 2");
        selectBox->addItem("Option 3");
        section3Layout->addWidget(selectBox);

        // Add sections to the stacked widget
        stackedWidget->addWidget(section1);
        stackedWidget->addWidget(section2);
        stackedWidget->addWidget(section3);

        // Add the button panel and the stacked widget to the splitter
        splitter->addWidget(buttonPanel);
        splitter->addWidget(stackedWidget);
        splitter->setStretchFactor(1, 2);  // Make the right panel wider

        // Add the splitter to the layout
        layout->addWidget(splitter);

        // Connect the buttons to switch between the sections in the stacked widget
        connect(section1Button, &QPushButton::clicked, [=]() {
            stackedWidget->setCurrentIndex(0);
        });

        connect(section2Button, &QPushButton::clicked, [=]() {
            stackedWidget->setCurrentIndex(1);
        });

        connect(section3Button, &QPushButton::clicked, [=]() {
            stackedWidget->setCurrentIndex(2);
        });

        // Set window title and size
        setWindowTitle("Graphical User Interface for SciNumTools");
        resize(800, 600);
    }
};

int main(int argc, char * argv[]) {
  QApplication app(argc, argv);
  
  MainWindow mainWindow;
  mainWindow.show();

  return app.exec();
}
