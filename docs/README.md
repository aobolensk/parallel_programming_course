# Parallel Programming Course Documentation

### How to make and test your changes

1. Navigate to the documentation directory:
```bash
cd parallel_programming_course/docs
```

2. (Optional) Create a virtual environment:
```bash
python3 -m venv venv
```

3. Install the required dependencies:
```bash
pip install -r requirements.txt
```

4. Configure the documentation build:
```bash
cmake -S . -B build -DUSE_DOCS=ON
```

5. Generate API documentation with Doxygen:
```bash
doxygen Doxyfile
```

6. Build the documentation:
```bash
cmake --build build -t docs_html
```

7. Update the documentation:
```bash
cmake --build build -t docs_gettext
# update documentation
cmake --build build -t docs_update
```

8. Re-build the documentation:
```bash
cmake --build build -t docs_html
```

9. Make local deployment of the changes:
```bash
cd _build/html
python3 -m http.server 8080
```

10. Open the documentation in your browser:
```bash
open http://localhost:8080/en
open http://localhost:8080/ru
```
