/*
#include <d3d9.h>
#include <d3dx9.h>

// 전역 변수
LPDIRECT3D9             g_pD3D = NULL;        // Direct3D 객체
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL;  // Direct3D 디바이스
LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL;         // 정점 버퍼

// 정점 구조체
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)
struct CUSTOMVERTEX
{
    D3DXVECTOR3 position; // 정점의 위치
    DWORD color;          // 정점의 색상
};

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
    if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice)))
    {
        return E_FAIL;
    }

    // 정점 버퍼 생성
    if (FAILED(g_pd3dDevice->CreateVertexBuffer(3 * sizeof(CUSTOMVERTEX), 0, D3DFVF_CUSTOMVERTEX,
        D3DPOOL_DEFAULT, &g_pVB, NULL)))
    {
        return E_FAIL;
    }

    // 정점 데이터 설정
    VOID* pVertices;
    if (FAILED(g_pVB->Lock(0, 0, (void**)&pVertices, 0)))
        return E_FAIL;

    CUSTOMVERTEX vertices[] =
    {
        { D3DXVECTOR3(0.0f,  1.0f, 0.0f), D3DCOLOR_XRGB(255, 0, 0) }, // 빨간색 정점
        { D3DXVECTOR3(1.0f, -1.0f, 0.0f), D3DCOLOR_XRGB(0, 255, 0) }, // 초록색 정점
        { D3DXVECTOR3(-1.0f, -1.0f, 0.0f), D3DCOLOR_XRGB(0, 0, 255) }  // 파란색 정점
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
    if (FAILED(g_pd3dDevice->BeginScene()))
        return;

    // 화면 지우기
    g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    // 정점 버퍼 설정
    g_pd3dDevice->SetStreamSource(0, g_pVB, 0, sizeof(CUSTOMVERTEX));
    g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);

    // 삼각형 그리기
    g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

    // 장면 종료
    g_pd3dDevice->EndScene();

    // 화면에 표시
    g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

// 애플리케이션 진입점
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // 윈도우 클래스 등록
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, WindowProc,
                      0, 0, hInstance, NULL, LoadCursor(NULL, IDC_ARROW),
                      (HBRUSH)(COLOR_WINDOW + 1), NULL, "D3D Tutorial", NULL };
    RegisterClassEx(&wc);

    // 윈도우 생성
    HWND hWnd = CreateWindow("D3D Tutorial", "D3D Tutorial 01: Simple Triangle",
        WS_OVERLAPPEDWINDOW, 100, 100, 800, 600,
        NULL, NULL, hInstance, NULL);
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
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            Render();
        }
    }

    // 정리
    Cleanup();

    return (int)msg.wParam;
}
*/