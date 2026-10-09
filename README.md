# NetBSD ls(1) Utility - Midterm Project

## Thông tin dự án
- **Môn học:** Lập trình hệ thống
- **Giảng viên hướng dẫn:** TS. Nguyễn Nhật Ân
- **Sinh viên thực hiện:** Lê Thị Yến Nhi
- **Mã sinh viên:** 24IT193
- **Lớp:** Lập trình hệ thống (6)
- **Hệ điều hành thử nghiệm:** NetBSD 10.1 (x86_64)

---

## 1. Giới thiệu
Dự án này triển khai lại tiện ích hệ thống `ls(1)` trên hệ điều hành NetBSD bằng ngôn ngữ C. Chương trình đọc nội dung thư mục, lấy thuộc tính tệp qua lời gọi hệ thống `lstat()`, xử lý định dạng hiển thị và sắp xếp theo chuẩn NetBSD Manual Page.

---

## 2. Cấu trúc Mã nguồn (Modular Code)
Dự án được tổ chức theo chuẩn quy hoạch mã nguồn POSIX/UNIX:

```text
LeThiYenNhi_24IT193_Midterm/
├── include/               # Thư mục tệp tiêu đề (.h)
│   ├── options.h          # Khai báo cấu trúc Options & prototype parse_options()
│   ├── ls.h               # Khai báo cấu trúc FileInfo & prototype process_path()
│   └── display.h          # Khai báo prototype display_files()
├── src/                   # Thư mục tệp mã nguồn C (.c)
│   ├── options.c          # Xử lý tham số dòng lệnh bằng getopt()
│   ├── display.c          # Định dạng quyền hạn, UID/GID, thời gian, cờ -F và in -l
│   └── main.c             # Điểm nhập chương trình, qsort() và đệ quy -R
├── .gitignore             # Bỏ qua tệp thực thi và tệp rác nhị phân (.o, my_ls)
├── Makefile               # Kịch bản tự động biên dịch dự án bằng BSD Make / GCC
└── README.md              # Tài liệu hướng dẫn sử dụng và báo cáo dự án
```
## HƯỚNG DẪN BIÊN DỊCH VÀ CHẠY CHƯƠNG TRÌNH
1. Tải dự án từ GitHub
Bash
git clone [https://github.com/ltynhi/LeThiYenNhi_24IT193_Midterm.git](https://github.com/ltynhi/LeThiYenNhi_24IT193_Midterm.git)
cd LeThiYenNhi_24IT193_Midterm
2. Biên dịch mã nguồn
Sử dụng công cụ make tích hợp sẵn trên NetBSD để biên dịch tự động: make
Lệnh này sẽ gọi gcc biên dịch các tệp trong src/ và tạo ra file thực thi my_ls ở thư mục gốc.
3. Các lệnh thực thi mẫu
Liệt kê chi tiết bao gồm tệp ẩn (trừ . và ..):
./my_ls -lA
Hiển thị chi tiết kèm ký tự phân loại loại tệp (/, *):
./my_ls -lF
Hiển thị chi tiết với UID và GID dạng số:
./my_ls -ln
Hiển thị danh sách sắp xếp theo dung lượng giảm dần:
./my_ls -lS
Kết hợp đệ quy thư mục con và sắp xếp theo thời gian:
./my_ls -lRt
Kiểm tra với đường dẫn cụ thể:
./my_ls -lF /usr/bin
4. Dọn dẹp tệp biên dịch
Để xóa các tệp object (.o) và tệp thực thi my_ls đưa thư mục về trạng thái ban đầu:
make clean
