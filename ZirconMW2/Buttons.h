//Local Button Monitoring By SC58 and Milky4444
namespace ButtonMonitoring
{  
    enum Buttons
    {
                L1 = 0x41,
                R1 = 0x4D,
                Square = 0x29,
                R3 = 0xD1,
                DpadUp = 0xF5,
                DpadDown = 0x105,
                Cross = 0x11,
                Triangle = 0x34,
                Circle = 0x1D,
                L2 = 0xDC,
                R2 = 0xE8,
                L3 = 0xC4,
                Left = 0x10D,
                Right =  0x119,
                Select = 0xB8,
                Start = 0xAC
    };
    bool ButtonPressed(Buttons Button)
    {
	    return (*(char*)(0x0095C08A + Button) != 0);
    }
}