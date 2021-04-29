#include "notepad.h"
#include "ui_notepad.h"

Notepad::Notepad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Notepad)
{
    // Setup the User Interface object
    ui->setupUi(this);

    // Have the textedit widget take up the whole window
    this->setCentralWidget(ui->textEdit);

    // Set the title for the window to the file name
    setWindowTitle("unnamed - NotepadQt");

    // Set the window icon
    setWindowIcon(QIcon(":/resources/Notepad-icon_2.png"));

    // Chcecking directory existence
    QString pth = "C:/Users/wkonior/Documents/QtProjects/NotepadQt";
    QDir dir(pth);
    foreach(QFileInfo var, dir.entryInfoList()){
        if(var.isDir()) ui->textEdit->append(QString("Dir: " + var.absoluteFilePath()));
        if(var.isFile()) ui->textEdit->append(QString("File: " + var.absoluteFilePath()));
    }

//    // Checking existence, creating and deleting directory
//    pth += "/NewFolder";
//    QDir dir2(pth);
//    if (dir2.exists()) {
//        QMessageBox::information(this, "Info", "Directory " + QString(dir2.path()) + " exists. Removing ..");
//        dir2.rmpath(pth);
//    }
//    else {
//        QMessageBox::critical(this, "Info", "Directory " + QString(dir2.path()) + " doesn't exists. Creating ..");
//        dir2.mkpath(pth);
//    }
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
    setWindowTitle("unnamed - NotepadQt");

    // Pop-up the new-info in statusbar
    this->statusBar()->showMessage("New file initialized");
}

void Notepad::on_actionOpen_triggered()
{
    // Define filters for open file dialog
    QString filter = "All Files (*.*) ;; Text Files (*.txt) ;; XML Files (*.xml)";

    // Opens a dialog that allows you to select a file to open
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file", QDir::homePath(), filter);

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
    this->setWindowTitle(fileName + " - NotepadQt");

    // Interface for reading text
    QTextStream in(&file);

    // Copy text in the string
    QString text = in.readAll();

    // Put the text in the textEdit widget
    ui->textEdit->setText(text);

    // Close the file
    file.close();

    // Status Bar message
    this->statusBar()->showMessage("The " + currentFile + " file opened sucessfully");
}

void Notepad::on_actionSave_triggered()
{
    // Opens a dialog that allows you to save a file
    QString fileName = QFileDialog::getSaveFileName(this, "Save", QDir::homePath());

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

    // Inteface for writing the string define the stream object
    QTextStream out(&file);

    // Put the text into the QString text variable
    QString text = ui->textEdit->toPlainText();

    // Put the string into the stream of text
    out << text;

    // Close the file
    file.flush();
    file.close();

    // Status Bar message
    this->statusBar()->showMessage("The file saved as " + currentFile);
}

void Notepad::on_actionSave_As_triggered()
{
    // Opens a dialog that allows you to save a file
    QString fileName = QFileDialog::getSaveFileName(this, "Save", QDir::homePath());

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

    // Inteface for writing the string define the stream object
    QTextStream out(&file);

    // Put the text into the QString text variable
    QString text = ui->textEdit->toPlainText();

    // Put the string into the stream of text
    out << text;

    // Close the file
    file.flush();
    file.close();

    // Status Bar message
    this->statusBar()->showMessage("The file saved as " + currentFile);
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

    // Status Bar message
    this->statusBar()->showMessage("Print request is sent");
}

void Notepad::on_actionClose_triggered()
{
    QApplication::quit();
}

void Notepad::on_actionUndo_triggered()
{
    ui->textEdit->undo();

    // Status Bar message
    this->statusBar()->showMessage("Undo");
}

void Notepad::on_actionRedo_triggered()
{
    ui->textEdit->redo();

    // Status Bar message
    this->statusBar()->showMessage("Redo");
}

void Notepad::on_actionCopy_triggered()
{
    ui->textEdit->copy();

    // Status Bar message
    this->statusBar()->showMessage("Text copied");
}

void Notepad::on_actionCut_triggered()
{
    ui->textEdit->cut();

    // Status Bar message
    this->statusBar()->showMessage("Text cut");
}

void Notepad::on_actionPaste_triggered()
{
    ui->textEdit->paste();

    // Status Bar message
    this->statusBar()->showMessage("Text pasted");
}



void Notepad::on_actionFont_triggered()
{
    // Create font object and get the font from the dialog
    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);

    if(ok){
        ui->textEdit->setFont(font);
    }
    else
        return;

}

void Notepad::on_actionColor_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose color");

    if(color.isValid()){
        ui->textEdit->setTextColor(color);
    }
    else
        return;
}

void Notepad::on_actionAbout_triggered()
{
    QString about_text = "";
    about_text += "Author : Wojciech Konior\n";
    about_text += "Date : 29-04-2021\n";
    about_text += "(C) NotepadQt (R)\n";

    QMessageBox::about(this, "About NotepadQt", about_text);
}
