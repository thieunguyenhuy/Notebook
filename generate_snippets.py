import os

# --- CẤU HÌNH ---
# Thư mục GỐC chứa các thư mục con (math, graph, string...)
SOURCE_ROOT = r"D:/Code/Notebook" 

# Thư mục đích của Sublime Text (Nên gom vào 1 folder riêng cho gọn)
DEST_DIR = r"C:/Users/LENOVO/AppData/Roaming/Sublime Text 3/Packages/User"

EXTENSIONS = ('.h', '.hpp', '.cpp')
TRIGGER_PREFIX = "@"

def create_snippet_xml(content, trigger, relative_path):
    # relative_path giúp hiển thị nguồn gốc file trong menu gợi ý
    # Ví dụ: description sẽ hiện "CP: graph/dsu.h" thay vì chỉ "dsu"
    template = f"""<snippet>
    <content><![CDATA[
{content}
]]></content>
    <tabTrigger>{trigger}</tabTrigger>
    <scope>source.c++, source.c</scope>
    <description>{relative_path}</description>
</snippet>"""
    return template

def main():
    # Tạo thư mục đích nếu chưa có
    if not os.path.exists(DEST_DIR):
        print(f"No directory: {DEST_DIR}")
        return

    count = 0
    
    # os.walk sẽ đi sâu vào từng thư mục con
    for root, dirs, files in os.walk(SOURCE_ROOT):
        for filename in files:
            if filename.endswith(EXTENSIONS):
                # 1. Đường dẫn file đầy đủ
                full_path = os.path.join(root, filename)
                
                # 2. Lấy đường dẫn tương đối để làm Description cho đẹp
                # Ví dụ: graph/dsu.h
                rel_path = os.path.relpath(full_path, SOURCE_ROOT)
                
                # 3. Đọc nội dung
                try:
                    with open(full_path, 'r', encoding='utf-8') as f:
                        content = f.read()
                except Exception as e:
                    print(f"Error reading {rel_path}: {e}")
                    continue

                # 4. Tạo trigger từ tên file (bỏ đuôi mở rộng)
                # Lưu ý: Nếu bạn có graph/bfs.h và tree/bfs.h, 
                # file sau sẽ ghi đè file trước vì trùng trigger "bfs".
                # Hãy đặt tên file duy nhất (vd: graph_bfs.h, tree_bfs.h)
                raw_name = os.path.splitext(filename)[0]
                trigger_name = f"{TRIGGER_PREFIX}{raw_name}"
                
                # 5. Tạo nội dung XML
                snippet_content = create_snippet_xml(content, trigger_name, rel_path)
                
                # 6. Ghi file snippet
                dest_filename = f"{trigger_name}.sublime-snippet"
                dest_path = os.path.join(DEST_DIR, dest_filename)
                
                with open(dest_path, 'w', encoding='utf-8') as f:
                    f.write(snippet_content)
                
                print(f"Generated: {trigger_name} \t(from {rel_path})")
                count += 1

    print(f"\n--- SUCCESS: Updated {count} snippets form subdirectories! ---")

if __name__ == "__main__":
    main()