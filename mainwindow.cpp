#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete buddy_;
    delete ui;
}

void MainWindow::on_allocateBtt_clicked()
{
    //만약에 입력값이 없다면.
    if(ui->allocateInput->text().isEmpty())
    {
        ui->consoleOut->setPlainText("Insert Allocating Size)");
        return;
    }


    //만약 하한선 보다 작은 값을 넣으면
    if(ui->allocateInput->text().toInt() <= 2)
    {
        ui->consoleOut->setPlainText("Minimum size is 2KB. :)");
        return;
    }

    // 여기까지가 입력 오류로 실패한 경우




    double allocatedMem = 0;

   allocatedMem = buddy_->AskAllocation(ui->allocateInput->text().toDouble());

   if(allocatedMem > 0)
   {
       string newString = std::to_string(allocatedMem) + "KB Allocated.";
       QString newQString = QString::fromStdString(newString);

       ui->consoleOut->setPlainText(newQString);
   } else
   {
       ui->consoleOut->setPlainText("Failed:Allocating Overflow?");
   }

   //가용 메모리를 QString으로 변환해 입력해 넣기
   QString newText;
   newText = QString::number(buddy_->GetMemoryLeft());

   ui->pMemoryDisplay->setText(newText);


}


//해제 버튼을 눌렀을때
void MainWindow::on_releaseBtt_clicked()
{
    //만약에 입력값이 없다면.
    if(ui->releaseInput->text().isEmpty())
    {
        ui->consoleOut->setPlainText("Insert Releasing Size");
        return;
    }

    if(ui->releaseInput->text().toDouble() <=2)
    {
        ui->consoleOut->setPlainText("Minimum Size is 2KB");
        return;
    }
    // 여기까지가 입력 오류로 실패한 경우

    double releasedMem = 0;

   releasedMem = buddy_->ReleaseMemory(ui->allocateInput->text().toDouble());

   if(releasedMem > 0)
   {
       string newString = std::to_string(releasedMem) + "KB Released.";
       QString newQString = QString::fromStdString(newString);

       ui->consoleOut->setPlainText(newQString);
   } else
   {
       ui->consoleOut->setPlainText("Failed(OVERFLOW): Tried releasing size bigger than allocated size?");
   }

   //가용 메모리를 QString으로 변환해 입력해 넣기
   QString newText;
   newText = QString::number(buddy_->GetMemoryLeft());

   ui->pMemoryDisplay->setText(newText);

}


//세팅/리셋 버튼을 눌렀을때
void MainWindow::on_setBtt_clicked()
{
    if(ui->totalMemoryInput->text().isEmpty())
    {
        ui->consoleOut->setPlainText("First, insert Physical Memory");
        return;
    }

    if(ui->totalMemoryInput->text().toDouble() <=0)
    {
        ui->consoleOut->setPlainText("Pleas input bigger than 0");
        return;
    }


    //토탈 메모리 설정.
    totalMemory = ui->totalMemoryInput->text().toDouble();

    //리셋팅
   buddy_ = NULL;
   // 새롭게 피지컬 메모리를 세팅
   buddy_ = new BuddyAllocater(totalMemory);

   //가용 메모리를 QString으로 변환해 입력해 넣기
   QString newText;
   newText = QString::number(buddy_->GetMemoryLeft());

   ui->pMemoryDisplay->setText(newText);

   return;
}
