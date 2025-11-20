#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#include <winrt/Microsoft.UI.Windowing.h>   // AppWindow
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.
namespace winrt::Q2_1::implementation
{
    MainWindow::MainWindow()
    {
        InitializeComponent();              // WinUI 3: Window.AppWindow()
        if (auto aw = this->AppWindow())
        {
            aw.Resize({ 320, 240 });        // 창 크기 320 * 240
        }
    }
    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }
}

void winrt::Q2_1::implementation::MainWindow::plusButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    double inputValue1, inputValue2, outputValue;
    if (firstInputBox().Text().empty())         // 빈칸인 상태로 버튼을 누르면 오류가 남
        inputValue1 = 0.0;
    else
        inputValue1 = std::stod(firstInputBox().Text().c_str());
    if (secondInputBox().Text().empty())        // 빈 칸이면 0으로 설정
        inputValue2 = 0.0;
    else
        inputValue2 = std::stod(secondInputBox().Text().c_str());

    outputValue = inputValue1 + inputValue2;

    auto str = std::to_wstring(outputValue);

    str.erase(str.find_last_not_of(L'0') + 1);  // 끝자리 0 제거
    if (!str.empty() && str.back() == L'.')     // 마지막이 소수점이면 제거
        str.pop_back();

    outputBox().Text(str);
}
