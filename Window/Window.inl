template<typename render>
void Window::MessageLoopRun(render renderfunc)
{
    MSG msg = { };

    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
        else
        {
            renderfunc();
        }

    }
    printf("WM_QUIT wParam = %llu\n",
       static_cast<unsigned long long>(msg.wParam));

    unsigned long long wm_quit_message = static_cast<unsigned long long>(msg.wParam);

    std::exit(wm_quit_message);

}
