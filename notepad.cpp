#include "notepad.h"
#include "ui_notepad.h"

Notepad::Notepad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Notepad)
{
    // Setup the UI
    ui->setupUi(this);

    // Have the textedit widget take up the whole window
    this->setCentralWidget(ui->textEdit);

    // Set the title for the window to the file name
    setWindowTitle("unnamed - QtNotepad");
}

Notepad::~Notepad()
{
    delete ui;
}


void Notepad::on_actionNew_triggered()
{
    // Global referencing the current file that we are clearing
    currentFile.clear();

    // Clear the textEdt widget buffer
    ui->textEdit->setText(QString());

    // Set the title for the window to unnamed
    setWindowTitle("unnamed - QtNotepad");
}

void Notepad::on_actionOpen_triggered()
{
    // Opens a dialog that allows you to select a file to open
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");

    // An object for reading and writing files
    QFile file(fileName);

    // Store the current File name
    currentFile = fileName;

    //Try to open the file as a read only or display a warning
    if(!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }

    // Set the title for the window to the file name
    setWindowTitle(fileName + " - QtNotepad");

    // Interface for reading text
    QTextStream in(&file);

    // Copy text in the string
    QString text = in.readAll();

    // Put the text in the textEdit widget
    ui->textEdit->setText(text);

    // Close the file
    file.close();
}

void Notepad::on_actionSave_As_triggered()
{
    // Opens a dialog that allows you to save a file
    QString fileName = QFileDialog::getSaveFileName(this, "Save");

    // Define an object for writing file
    QFile file(fileName);

    // Try to open the file as a write only text file or display a warning
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    // Store the current name of the file
    currentFile = fileName;

    // Set the title for the window to the file name
    setWindowTitle(fileName + " - QtNotepad");

    // Inteface for writing the string
    QTextStream out(&file);

    // Put the text into the QString variable
    QString text = ui->textEdit->toPlainText();

    // Put the string to the stream of text
    out << text;

    // Close the file
    file.close();
}

void Notepad::on_actionPrint_triggered()
{
    // Allows for interacting with printer
    QPrinter printer;

    // You'll put your printer name here
    printer.setPrinterName("Printer Name");

    // Create the print dialog and pass the name and parent
    QPrintDialog pDialog(&printer, this);

    // Try to find the printer or display a warning
    if(pDialog.exec() == QDialog::Rejected){
        QMessageBox::warning(this, "Warning", "Cannot Access Printer");
        return;
    }

    // Send the text to the printer
    ui->textEdit->print(&printer);
}

void Notepad::on_actionClose_triggered()
{
    QApplication::quit();
}

void Notepad::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void Notepad::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void Notepad::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void Notepad::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void Notepad::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}
