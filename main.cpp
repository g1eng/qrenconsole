#include <iostream>
#include <qrencode.h>

/// Print left or right margin for enhanced visibility.
static void print_horizontal_margin(){
    std::cout << "\033[01;107m        \033[00m";
}

/// Print top or bottom margin for enhanced visibility.
static void print_vertical_margin(int width){
    int i;
    print_horizontal_margin();
    print_horizontal_margin();
    for (i = 0; i < width; i++ ) {
        std::cout << "\033[01;107m \033[00m";
    }
    std::cout << std::endl;
}

/// Show version
void show_version() {
    std::cerr
            << "qrenconsole v0.1.0 - licensed under GPLv2 by Nomura Suzume"
            << std::endl;
}

/// Show usage
void show_usage(){
    show_version();
    std::cerr
            << "Any words from stdin will be converted to inline QR code:"
            << std::endl;
}

/// Convert string into ASCII QR code lines.
/// For coloring detail, see https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
int convert_to_ascii_qr(std::string s){

    QRcode *qrcode;
    unsigned char* ref;
    int i, j, bitshift;
    uint64_t img_bit;

    if (s.length() == 0) {
        std::cerr << "null line detected!";
        return 1;
    } else if (s == "\n") {
        std::cerr << "no description";
        show_usage();
        return 1;
    }
    qrcode = QRcode_encodeString8bit(
            s.c_str(),
            1,
            QR_ECLEVEL_M
    );
    unsigned char* ref_root = qrcode->data;

    //top margin
    print_vertical_margin(qrcode->width);
    print_vertical_margin(qrcode->width);

    for (i = 0; i < qrcode->width; i++ ) {
        //left margin
        print_horizontal_margin();

        //body
        for (j=0; j < qrcode->width; j++) {
            bitshift = (i + j * qrcode->width);
            ref = ref_root + bitshift;
            img_bit = uint64_t (*ref);
            if ( img_bit % 2 == 1) {
                std::cout << "\033[01;40m \033[00m";
            } else {
                std::cout << "\033[01;107m \033[00m";
            };
        }
        //right margin
        print_horizontal_margin();
        //next
        std::cout << std::endl;
    }

    //bottom margin
    print_vertical_margin(qrcode->width);
    print_vertical_margin(qrcode->width);

    std::cerr << std::endl << "EOF" << std::endl;
    QRcode_free(qrcode);

    return 0;
}

int main() {

    std::string s;
    show_usage();

    while (std::cin >> s) {
        std::cout << "<target> " << s << std::endl;
        convert_to_ascii_qr(s);
    }

    return 0;
}
