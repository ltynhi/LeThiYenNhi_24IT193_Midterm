# NetBSD ls(1) Midterm Implementation

## Thông tin sinh viên
- **Họ và tên:** Lê Thị Yến Nhi
- **Mã sinh viên:** 24IT193
- **Hệ điều hành thử nghiệm:** NetBSD 10.1 (x86_64)

---

## 1. Giới thiệu dự án
Dự án này tái hiện lại công cụ hệ thống `ls(1)` trên hệ điều hành NetBSD bằng ngôn ngữ C. Chương trình đọc nội dung thư mục, lấy thông tin thuộc tính tệp qua các lời gọi hệ thống (`stat`, `lstat`), xử lý định dạng hiển thị và sắp xếp danh sách tệp theo yêu cầu của các cờ tùy chọn (options).

---

## 2. Cấu trúc thư mục
Dự án được tổ chức theo mô hình mã nguồn sạch (Modular Code) chuẩn POSIX/UNIX:

```text
LeThiYenNhi_24IT193_Midterm/
├── include/            # Thư mục chứa các tệp header (.h)
│   ├── display.h       # Khai báo hàm hiển thị danh sách file
│   ├── ls.h            # Cấu trúc dữ liệu FileInfo và prototype hàm xử lý thư mục
│   └── options.h        # Cấu trúc lưu trạng thái options và hàm parse_options
├── src/                # Thư mục chứa mã nguồn C (.c)
│   ├── display.c       # Định dạng quyền truy cập, UID/GID, thời gian, cờ -F và định dạng -l
│   ├── main.c          # Điểm vào chính, hàm so sánh (qsort) và xử lý đệ quy -R
│   └── options.c       # Xử lý tham số dòng lệnh với getopt()
├── .gitignore          # Chặn commit các tệp binary/object (.o, my_ls)
├── Makefile            # Kịch bản tự động biên dịch dự án
└── README.md           # Báo cáo hướng dẫn dự án