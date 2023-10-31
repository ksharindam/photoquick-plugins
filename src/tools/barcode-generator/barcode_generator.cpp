/*  This file is a part of PhotoQuick Plugins project, and is GNU GPLv3 licensed
    Copyright (C) 2021-2023 Arindam Chaudhuri <ksharindam@gmail.com>
*/
#include "barcode_generator.h"
#include <QGridLayout>
#include <QDialogButtonBox>
#include <QPainter>
#include <QDebug>
#include <cmath>


#define PLUGIN_NAME "Barcode Generator"
#define PLUGIN_MENU "Tools/Barcode Generator"
#define PLUGIN_VERSION "1.0"

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    Q_EXPORT_PLUGIN2(barcode-generator, ToolPlugin);
#endif



std::vector<QString> data = {
// widths    A           B           C
"212222",   " ",        " ",        "00",
"222122",   "!",        "!",        "01",
"222221",   "\"",       "\"",       "02",
"121223",   "#",        "#",        "03",
"121322",   "$",        "$",        "04",
"131222",   "%",        "%",        "05",
"122213",   "&",        "&",        "06",
"122312",   "'",        "'",        "07",
"132212",   "(",        "(",        "08",
"221213",   ")",        ")",        "09",
"221312",   "*",        "*",        "10",
"231212",   "+",        "+",        "11",
"112232",   ",",        ",",        "12",
"122132",   "-",        "-",        "13",
"122231",   ".",        ".",        "14",
"113222",   "/",        "/",        "15",
"113222",   "0",        "0",        "16",
"123221",   "1",        "1",        "17",
"223211",   "2",        "2",        "18",
"221132",   "3",        "3",        "19",
"221231",   "4",        "4",        "20",
"213212",   "5",        "5",        "21",
"223112",   "6",        "6",        "22",
"312131",   "7",        "7",        "23",
"311222",   "8",        "8",        "24",
"321122",   "9",        "9",        "25",
"321221",   ":",        ":",        "26",
"312212",   ";",        ";",        "27",
"322112",   "<",        "<",        "28",
"322211",   "=",        "=",        "29",
"212123",   ">",        ">",        "30",
"212321",   "?",        "?",        "31",
"232121",   "@",        "@",        "32",
"111323",   "A",        "A",        "33",
"131123",   "B",        "B",        "34",
"131321",   "C",        "C",        "35",
"112313",   "D",        "D",        "36",
"132113",   "E",        "E",        "37",
"132311",   "F",        "F",        "38",
"211313",   "G",        "G",        "39",
"231113",   "H",        "H",        "40",
"231311",   "I",        "I",        "41",
"112133",   "J",        "J",        "42",
"112331",   "K",        "K",        "43",
"132131",   "L",        "L",        "44",
"113123",   "M",        "M",        "45",
"113321",   "N",        "N",        "46",
"133121",   "O",        "O",        "47",
"313121",   "P",        "P",        "48",
"211331",   "Q",        "Q",        "49",
"231131",   "R",        "R",        "50",
"213113",   "S",        "S",        "51",
"213311",   "T",        "T",        "52",
"213131",   "U",        "U",        "53",
"311123",   "V",        "V",        "54",
"311321",   "W",        "W",        "55",
"331121",   "X",        "X",        "56",
"312113",   "Y",        "Y",        "57",
"312311",   "Z",        "Z",        "58",
"332111",   "[",        "[",        "59",
"314111",   "\\",       "\\",       "60",
"221411",   "]",        "]",        "61",
"431111",   "^",        "^",        "62",
"111224",   "_",        "_",        "63",
"111422",   "\x00",     "`",        "64",
"121124",   "\x01",     "a",        "65",
"121421",   "\x02",     "b",        "66",
"141122",   "\x03",     "c",        "67",
"141221",   "\x04",     "d",        "68",
"112214",   "\x05",     "e",        "69",
"112412",   "\x06",     "f",        "70",
"122114",   "\x07",     "g",        "71",
"122411",   "\x08",     "h",        "72",
"142112",   "\t",       "i",        "73",
"142211",   "\n",       "j",        "74",
"241211",   "\v",       "k",        "75",
"221114",   "\f",       "l",        "76",
"413111",   "\r",       "m",        "77",
"241112",   "\x0e",     "n",        "78",
"134111",   "\x0f",     "o",        "79",
"111242",   "\x10",     "p",        "80",
"121142",   "\x11",     "q",        "81",
"121241",   "\x12",     "r",        "82",
"114212",   "\x13",     "s",        "83",
"124112",   "\x14",     "t",        "84",
"124211",   "\x15",     "u",        "85",
"411212",   "\x16",     "v",        "86",
"421112",   "\x17",     "w",        "87",
"421211",   "\x18",     "x",        "88",
"212141",   "\x19",     "y",        "89",
"214121",   "\x1a",     "z",        "90",
"412121",   "\x1b",     "{",        "91",
"111143",   "\x1c",     "|",        "92",
"111341",   "\x1d",     "}",        "93",
"131141",   "\x1e",     "~",        "94",
"114113",   "\x1f",     "DEL",      "95",
"114311",   "FNC3",     "FNC3",     "96",
"411113",   "FNC2",     "FNC2",     "97",
"411311",   "ShiftB",   "ShiftA",   "98",
"113141",   "CodeC",    "CodeC",    "99",
"114131",   "CodeB",    "FNC4",     "CodeB",
"311141",   "FNC4",     "CodeA",    "CodeA",
"411131",   "FNC1",     "FNC1",     "FNC1",
"211412",   "StartA",   "StartA",   "StartA",
"211214",   "StartB",   "StartB",   "StartB",
"211232",   "StartC",   "StartC",   "StartC",
"2331112",  "Stop",     "Stop",     "Stop",
};

class Code128
{
public:
    Code128();
    void set_codeset_type(QString set);// "A", "B" or "C"
    // returns a vector of alternating bar and space widths
    std::vector<int> generate(QString text);

    std::vector<QString> WIDTHS;
    std::map<QString, int> A;
    std::map<QString, int> B;
    std::map<QString, int> C;

    std::map<QString, int> codeset;
    QString codeset_type;
};

bool is_digit(QString text);
bool need_a(QString text, int pos);
QImage drawBarcode(std::vector<int> bars, int img_w, int img_h, QString text);

Code128:: Code128()
{
    int rows = data.size()/4;
    for (int i=0; i<rows; i++){
        A.insert({data[i*4+1], i});
        B.insert({data[i*4+2], i});
        C.insert({data[i*4+3], i});
        WIDTHS.push_back(data[i*4]);
    }
}

void
Code128:: set_codeset_type(QString set)
{
    if (set=="A")
        codeset = A;
    else if (set=="B")
        codeset = B;
    else if (set=="C")
        codeset = C;
    else
        return;
    codeset_type = set;
}

// returns a vector of alternating bar and space widths
std::vector<int>
Code128:: generate(QString text)
{
    text = text.toLatin1();

    int len = text.size();
    std::vector<int> codes;
    // Start Code
    // C is effective if starts with atleast 4 digits,
    // or whole text consists of only two digits
    if ((len==2 and is_digit(text)) or (len>=4 and is_digit(text.left(4)))){
        set_codeset_type("C");
        codes.push_back(codeset["StartC"]);
    }
    else if (need_a(text,0)){
        set_codeset_type("A");
        codes.push_back(codeset["StartA"]);
    }
    else {
        set_codeset_type("B");
        codes.push_back(codeset["StartB"]);
    }

    // Data
    int pos = 0;
    while (pos < len) {
        if (codeset_type=="C" and len-pos>=2 and is_digit(text.mid(pos, 2))){
            codes.push_back(text.mid(pos,2).toInt());
            pos += 2;
        }
        else if ( (codeset_type=="A" or codeset_type=="B") and (
                    (len-pos>=6 and is_digit(text.mid(pos, 6))) or
                    (len-pos==4 and is_digit(text.mid(pos, 4))) )){
            codes.push_back(codeset["CodeC"]);
            set_codeset_type("C");
        }
        // switch to A if there is atleast one A-only character. and
        // there is no B-only character before that.
        else if ((codeset_type=="B" or codeset_type=="C") and need_a(text, pos)){
            codes.push_back(codeset["CodeA"]);
            set_codeset_type("A");
        }
        else if (codeset_type=="C" or (codeset_type=="A" and text.at(pos).unicode()>=96)){
            codes.push_back(codeset["CodeB"]);
            set_codeset_type("B");
        }
        else {
            codes.push_back(codeset[text.at(pos)]);
            pos++;
        }
    }

    // Checksum
    int checksum = 0;
    int weight = 0;
    for (int code : codes){
        checksum += std::max(weight, 1) * code;
        weight++;
    }
    codes.push_back(checksum % 103);

    // Stop Code
    codes.push_back(codeset["Stop"]);

    // calculate bars
    std::vector<int> barcode_widths;
    for (int code : codes){
        QString widths = WIDTHS[code];
        for (QChar &width : widths){
            barcode_widths.push_back(QString(width).toInt());
        }
    }
    return barcode_widths;
}

// should have atleast one of A-only characters and before that
// must not have any B-only character
bool need_a(QString text, int pos)
{
    for (int i=pos; i<text.size(); i++){
        int val = text.at(i).unicode();
        if (val>=96)// B-only character
            return false;
        if (val<32)// A-only character
            return true;
    }
    // all characters fit in B
    return false;
}

// works if val is in int range, i.e 2,147,483,647. which is fine here
bool is_digit(QString text)
{
    bool ok;
    text.toInt(&ok);
    return ok and text.at(0).isDigit();// this assures that first char is not negative sign
}



Dialog:: Dialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Barcode Generator");
    resize(250, 150);
    QGridLayout *layout = new QGridLayout(this);
    QLabel *label = new QLabel("Barcode Type : Code 128", this);
    textEdit = new QLineEdit(this);
    textEdit->setPlaceholderText("Enter Text...");
    generateBtn = new QPushButton("Generate", this);
    barcodeLabel = new QLabel(this);
    barcodeLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QPixmap pm(250,78);
    pm.fill();
    barcodeLabel->setPixmap(pm);
    QDialogButtonBox *btnBox = new QDialogButtonBox(
        QDialogButtonBox::Ok|QDialogButtonBox::Cancel, Qt::Horizontal, this);

    layout->addWidget(label, 0,0,1,2);
    layout->addWidget(textEdit, 1,0,1,2);
    layout->addWidget(generateBtn, 2,1,1,1);
    layout->addWidget(barcodeLabel, 3,0,1,2);
    layout->addWidget(btnBox, 4,0,1,2);

    connect(btnBox, SIGNAL(accepted()), this, SLOT(onAcceptClick()));
    connect(btnBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(generateBtn, SIGNAL(clicked()), this, SLOT(generateBarcode()));
}

void
Dialog:: onAcceptClick()
{
    if (not result.isNull())
        return accept();
    reject();
}


void
Dialog:: generateBarcode()
{
    Code128 code128;
    std::vector<int> bars = code128.generate(textEdit->text());
    result = drawBarcode(bars, 654, 202, textEdit->text());// 614x142 = 5.2x1.2cm @300 dpi
    barcodeLabel->setPixmap(QPixmap::fromImage(result.scaledToWidth(250,Qt::SmoothTransformation)));
}

QImage drawBarcode(std::vector<int> bars, int img_w, int img_h, QString text)
{
    int margin = 20;
    int barcode_w = img_w - 2*margin;
    int barcode_h = img_h - 3*margin;
    // calculate unit thickness of bars
    float sum = 20;// 10 units of quiet zone on each side
    for (int w : bars){
        sum += w;
    }
    float thickness = barcode_w/sum;

    QImage img(img_w, img_h, QImage::Format_RGB32);
    img.fill(Qt::white);
    img.setDotsPerMeterX(300/0.0254);
    img.setDotsPerMeterY(300/0.0254);

    QPainter painter(&img);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::NoPen));
    painter.setBrush(Qt::black);

    float x = margin + 10*thickness;
    bool bar = true;// bar or space
    for (int w : bars){
        if (bar){
            painter.drawRect(x,margin, w*thickness, barcode_h);
        }
        bar = not bar;
        x += w*thickness;
    }
    // draw text
    painter.setPen(QPen(Qt::black, 3));
    painter.drawText(QRect(0, margin+barcode_h, img_w, 2*margin), Qt::AlignCenter, text);
    // draw corners
    painter.drawLine(0,0, 0,margin);
    painter.drawLine(0,0, margin,0);
    painter.drawLine(img_w-1,0, img_w-1-margin,0);
    painter.drawLine(img_w-1,0, img_w-1,margin);
    painter.drawLine(0,img_h-1, 0,img_h-1-margin);
    painter.drawLine(0,img_h-1, margin,img_h-1);
    painter.drawLine(img_w-1,img_h-1, img_w-1-margin,img_h-1);
    painter.drawLine(img_w-1,img_h-1, img_w-1,img_h-1-margin);
    painter.end();
    return img;
}

// ************* ----------- The Plugin Class ---------- ***************

QString ToolPlugin:: menuItem()
{
    return QString(PLUGIN_MENU);
}

void ToolPlugin:: onMenuClick()
{
    Dialog *dialog = new Dialog(data->window);
    if (dialog->exec()==QDialog::Accepted){
        data->image = dialog->result;
        emit imageChanged();
        emit optimumSizeRequested();
    }
}
