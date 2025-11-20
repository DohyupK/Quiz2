#pragma once
#include "MainWindow.g.h"
#include <vector>
#include <winrt/Windows.UI.h>                                // Color
#include <winrt/Windows.Foundation.h>                        // Point, IInspectable
#include <winrt/Microsoft.UI.Xaml.Shapes.h>
#include <winrt/Microsoft.UI.Xaml.Input.h>
#include <winrt/Microsoft.UI.Xaml.Controls.Primitives.h>     // Slider ValueChanged args
#include <winrt/Microsoft.UI.Xaml.Media.h>
#include <winrt/Windows.Data.Json.h>                         // JSON
#include <windows.h>                                         // 파일 피커 (Win32 HWND 초기화용 인터페이스)
#include <Shobjidl_core.h>                                   // IInitializeWithWindow
#include <microsoft.ui.xaml.window.h>                        // IWindowNative (WinUI 3 Window → HWND)

namespace winrt::Q2_2::implementation
{
    // ======= 스트로크 데이터 구조 =======
    struct StrokeData
    {
        winrt::Windows::UI::Color color{};                        // 색상
        double thickness{ 2.0 };                                  // 굵기
        std::vector<winrt::Windows::Foundation::Point> points{};  // 좌표
    };

    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        // ===== 그리기 (포인터 이벤트) =====
        void DrawCanvas_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        void DrawCanvas_PointerMoved(winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        void DrawCanvas_PointerReleased(winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e);

        // ===== 툴바 이벤트 =====
        void PenColorPicker_ColorChanged(winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::Controls::ColorChangedEventArgs const& e);
        void ApplyColorButton_Click(winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void CloseColorFlyout_Click(winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void ThicknessSlider_ValueChanged(winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const& e);

        // ===== 저장/불러오기 이벤트 =====
        winrt::fire_and_forget SaveButton_Click(winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        winrt::fire_and_forget LoadButton_Click(winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

    private:
        // 현재 진행 중인 스트로크
        winrt::Microsoft::UI::Xaml::Shapes::Polyline m_currentStroke{ nullptr };
        StrokeData m_currentData{};
        bool m_isDrawing{ false };

        // 전역 펜 상태 (다음 스트로크에 적용)
        winrt::Windows::UI::Color m_currentColor{ 255, 0, 0, 0 };
        winrt::Windows::UI::Color m_pendingColor{ 255, 0, 0, 0 };
        double m_currentThickness{ 2.0 };

        // 완료된 스트로크 목록 (문서 모델)
        std::vector<StrokeData> m_strokes;

        // ===== 유틸 =====
        void UpdateColorPreview();                             // 색상 미리보기 업데이트
        void RedrawFromModel();                                // 모델 → 캔버스 재구성
        void InitializePickerWithWindow(winrt::Windows::Foundation::IInspectable const& picker); // FilePicker 초기화

        // 오류 메시지 다이얼로그
        winrt::Windows::Foundation::IAsyncAction ShowErrorDialog(winrt::hstring const& message);

    public:
        // 새로 그리기 버튼 클릭
        void NewButton_Click(winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::Q2_2::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
