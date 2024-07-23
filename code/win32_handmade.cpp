#include <windows.h>
#define internal static 
#define local_persist static
#define global_variable static

// TODO this is a global for now;
global_variable  bool running;

internal void
Win32ResizeDIBSection(int Width, int Height)
{
    BITMAPINFO BitmapInfo;
    BitmapInfo.bmiHeader.biSize = sizeof(BitmapInfo.bmiHeader);
    BitmapInfo.biWidth= Width;
    BitmapInfo.biHeight = Height;
    BitmapInfo.biPlanes = 1;
    BitmapInfo.biBitCount = 32;
    BitmapInfo.biCompression = BI_RGB;
    BitmapInfo.biSizeImage = 0;
    BitMapInfo.biXPelsPermeter = 0;
    BitMapInfo.biYPelsPerMeter = 0;
    BitmapInfo.biClrused = 0;
    BitmapInfo.biClrimportant = 0;
    

    void *BitmapMemory;
    HBITMAP BitmapHandle = CreateDIBSection(
        DevicContext,&BitmapInfo;
        DIB_RGB_COLORS,
        &BitMemory,
        0,0);
       
}
internal void
Win32UpdateWindow(HWND DeviceContext, int x, int y, width, height)
{
 
    StretchDIBits(DeviceContext,
                  x, y, width, height,
                  x, y, width, height,
                  const VOID       *lpBits,
                  const BITMAPINFO *lpbmi,
                  DIB_RGB_COLORS,SRCCOPY);

}



LRESULT CALLBACK
Win32MainWindowCallBack(HWND    Window,
                   UINT    Message,
                   WPARAM  WParam,
                   LPARAM  LParam
)
{
    LRESULT Result = 0;
    
    switch(Message)
    {
        case WM_SIZE:
        {
            RECT ClientRect;
            GetClientRect(Window,&ClientRect);
            int Height = ClientRect.bottom - ClientRect.top;
            int Width  = ClientRect.right - ClientRect.left;                  
            ResizeDIBSection(Width, Height);
            OutputDebugString("WM_SIZE\n");
        } break;

        case WM_DESTROY:
            
        {
            // TODO Handle this as an error - recreate window?
            running = false;
        } break;

        case WM_CLOSE:
        {
            // TODO Handle this with a message to the user?
            running = false;
        } break;

        case WM_ACTIVATEAPP:
        {
             OutputDebugString("WM_ACTIVATEAPP\n");
        } break;
        case WM_PAINT:
        {
            PAINTSTRUCT Paint;
            HDC DeviceContext= BeginPaint(Window, &Paint);
            int x = Paint.rcPaint.left;
            int y = Paint.rcPaint.top;
            int Height = Paint.rcPaint.bottom - Paint.rcPaint.top;
            int Width  = Paint.rcPaint.right - Paint.rcPaint.left;
            Win32UpdateWindow(DeviceContext ,x, y , Width, Height);
            EndPaint(Window, &Paint);
            
        } break;

        default:
        {
            //            OutputDebugString("DEFAULT\n");
            Result = DefWindowProc(Window, Message, WParam, LParam);
        } break; 
    }
    return(Result);
}

int CALLBACK
WinMain(HINSTANCE Instance,
HINSTANCE Previnstance,
LPSTR CommandLine,
int ShowCode)
{
    WNDCLASS WindowClass = {};
    
    // TODO : Check if HREDRAW/VREDRAW/OWNDC still matter
    WindowClass.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
    WindowClass.lpfnWndProc = Win32MainWindowCallBack;
    WindowClass.hInstance =Instance;
    // WindowClass.hIcon;
    WindowClass.lpszClassName = "HandmadeHeroClass";

    if(RegisterClass(&WindowClass))
    {
        HWND WindowHandle =
            CreateWindowExA(
            0,
            WindowClass.lpszClassName,
            "HandMadeHero",
            WS_OVERLAPPEDWINDOW|WS_VISIBLE,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            0,
            0,
            Instance,
            0);
        if(WindowHandle)
        {
            running = true;
            MSG Message;
            while(running)
            {
                BOOL MessageResult =  GetMessage(&Message,0,0,0);
                if(MessageResult > 0)
                {
                    TranslateMessage(&Message);
                    DispatchMessage(&Message);
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            // TODO: Logging
        }
    }
    else
    {
        // TODO: Logging 
    }
    
    return(0);
    
}
