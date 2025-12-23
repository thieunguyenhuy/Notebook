@echo off
:: Chuyển bảng mã sang UTF-8 để hiển thị tiếng Việt không bị lỗi (Optional)
chcp 65001 >nul

echo Dang cap nhat Snippets...
echo ------------------------------

:: Thay đường dẫn bên dưới bằng đường dẫn thật tới file python của bạn
python generate_snippets.py

echo.
echo ------------------------------
echo Xong!
:: Lệnh pause giúp cửa sổ không bị tắt ngay lập tức để bạn kịp xem lỗi (nếu có)
pause