#ifndef __serial_helper
#define __serial_helper

enum SerialAddr{
    ADDR_START = 1,
    ADDR_ALL = 0xF
};

enum SerialColor{
    SC_BLACK,
    SC_WHITE
};

/* Commands use a simple | separated value, except the first byte which is the task
    uint8_t addr
    uint8_t task
    data
*/
enum SerialCmd{
    CMD_SET_TEXT,       // (u8)size (hex)color (u8)font (str)text
    CMD_GET_TEXT,       // void - Asks button to reply with a REPL_KEYBOARD task. You have 500ms to do so
    CMD_SET_KEYBOARD, 
    CMD_REPL_KEYBOARD,  // (str)text - Replies with the content of the cap keyboard
    CMD_TOGGLE_BUTTON,  // 
};

namespace SerialHelper{

    void cmdSetText( SerialAddr addr, uint8_t size, uint8_t color, uint8_t font, char* text, char *output, size_t outputSize ){
        
        output[0] = addr;
        output[1] = CMD_SET_TEXT;
        output[2] = size;           // text size
        output[3] = color;          // 
        output[4] = font;           // Font identifier

        strncat(output+5, text, outputSize-6);
        output[outputSize-1] = 0; // Make sure it's null terminated

    }

    
};






#endif
