#include "DrawTriangle.h"

// 윈도우 프로시저 함수
LRESULT WINAPI WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

// 초기화 함수
HRESULT InitD3D(HWND hWnd)
{
    // Direct3D 객체 생성
    g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

    if (!g_pD3D)
        return E_FAIL;

    // 디바이스 초기화 설정
    D3DPRESENT_PARAMETERS d3dpp = {};
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
    d3dpp.BackBufferWidth = 800;
    d3dpp.BackBufferHeight = 600;
    d3dpp.hDeviceWindow = hWnd;
    d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

    // Direct3D 디바이스 생성
    if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice)))
    {
        return E_FAIL;
    }

    // 정점 버퍼 생성
    if (FAILED(g_pd3dDevice->CreateVertexBuffer(15 * sizeof(CUSTOMVERTEX), 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &g_pVB, NULL))) // 첫번째 매개변수는 정점의 개수를 의미한다. 삼각형 하나 => 3
    {
        return E_FAIL;
    }

    // 정점 데이터 설정
    VOID* pVertices;

    if (FAILED(g_pVB->Lock(0, 0, (void**)&pVertices, 0)))
        return E_FAIL;

    CUSTOMVERTEX vertices[]
    {
        // 첫번째 삼각형
        { 200.0f, 50.0f, 0.0f, 1.0f, D3DCOLOR_XRGB(255, 0, 0), },
        { 400.0f, 50.0f, 0.0f, 1.0f, D3DCOLOR_XRGB(255, 0, 0), },
        { 300.0f, 250.0f, 0.0f, 1.0f, D3DCOLOR_XRGB(255, 0, 0) },

        // 두번째 삼각형
        { 300.0f, 250.0f, 0.0f, 1.0f, D3DCOLOR_XRGB(255, 255, 255), },
        { 400.0f, 50.0f, 0.0f, 1.0f, D3DCOLOR_XRGB(255, 255, 255), },
        { 500.0f, 250.0f, 0.0f, 1.0f, D3DCOLOR_XRGB(255, 255, 255) },

        // 세번째 삼각형
        { 400.0f, 50.0f, 0.0f, 1.0f, D3DCOLOR_XRGB(0, 0, 255), },
        { 600.0f, 50.0f, 0.0f, 1.0f, D3DCOLOR_XRGB(0, 0, 255), },
        { 500.0f, 250.0f, 0.0f, 1.0f, D3DCOLOR_XRGB(0, 0, 255) },

        // 네번째 삼각형
        { 300.0f, 250.0f, 0.0f, 1.0f, D3DCOLOR_XRGB(0, 255, 0), },
        { 500.0f, 250.0f, 0.0f, 1.0f, D3DCOLOR_XRGB(0, 255, 0), },
        { 400.0f, 450.0f, 0.0f, 1.0f, D3DCOLOR_XRGB(0, 255, 0) },

        // 다섯번째 삼각형
        { 350.0f, 150.0f, 0.0f, 1.0f, D3DCOLOR_XRGB(255, 0, 0), },
        { 450.0f, 150.0f, 0.0f, 1.0f, D3DCOLOR_XRGB(0, 0, 255), },
        { 400.0f, 250.0f, 0.0f, 1.0f, D3DCOLOR_XRGB(0, 255, 0) }
    };

    memcpy(pVertices, vertices, sizeof(vertices));
    g_pVB->Unlock();

    return S_OK;
}

// 정리 함수
VOID Cleanup()
{
    if (g_pVB != NULL)
        g_pVB->Release();

    if (g_pd3dDevice != NULL)
        g_pd3dDevice->Release();

    if (g_pD3D != NULL)
        g_pD3D->Release();
}

// 렌더링 함수
VOID Render()
{
    // 장면 시작
    if (SUCCEEDED(g_pd3dDevice->BeginScene()))
    {
        // 화면 지우기
        g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

        // 정점 버퍼 설정
        g_pd3dDevice->SetStreamSource(0, g_pVB, 0, sizeof(CUSTOMVERTEX));
        g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
        
        // 삼각형 그리기
        g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 5); // 만들 도형의 개수

        // 장면 종료
        g_pd3dDevice->EndScene();

        // 화면에 표시
        g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
    }
}

// 애플리케이션 진입점
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, INT nCmdShow)
{
    // 윈도우 클래스 등록
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, WindowProc, 0, 0, hInstance, NULL, LoadCursor(NULL, IDC_ARROW), (HBRUSH)(COLOR_WINDOW + 1), NULL, "Draw Triangle", NULL };
    RegisterClassEx(&wc);

    // 윈도우 생성
    HWND hWnd = CreateWindow("Draw Triangle", "D3D_Draw Triangle", WS_OVERLAPPEDWINDOW, 100, 100, 800, 600, NULL, NULL, hInstance, NULL);

    if (!hWnd)
        return 0;

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // Direct3D 초기화
    if (FAILED(InitD3D(hWnd)))
        return 0;

    // 메인 루프
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg); // 키보드 입력 메시지를 문자 메시지로 변환한다.
            DispatchMessage(&msg); // 메시지를 해당 윈도우 프로시저로 전달하여 처리한다.
        }
        else
        {
            Render();
        }
    }

    Cleanup();
    return 0;
}