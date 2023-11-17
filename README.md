# Content-Based Image Retrieval

This project implements image segmentation, thresholding, and feature detection algorithms from scratch to classify images based on raw 2-Dimensional Data. It includes the creation of various 2-D and 3-D histograms for baseline matching, texture matching, object detection, multiple-histogram matching, contrast matching, etc.

## Operating System and Code Editor
- **Operating System:** Windows 10
- **Code Editor:** Visual Studio 2022

## Instructions

1. **Clone the Repository:**

    ```bash
    git clone https://github.com/your-username/your-repository.git
    ```

2. **Navigate to Project Directory:**

    ```bash
    cd your-repository
    ```

3. **Set Image Database Directory Path:**

    - Modify the directory path in the appropriate file to point to your image database.

4. **Run CSVwrite Script:**

    ```bash
    python CSVwrite.py
    ```

    - This classifies images in your custom database and writes features to a CSV file.

5. **CSV File Usage:**

    - The generated custom CSV file will serve the purpose of classifying images according to multiple histograms.

6. **Run CSVread Script:**

    ```bash
    python CSVread.py
    ```

7. **Select Matching Algorithms:**

    - Enter the number of matching images returned and press the following keys to select matching algorithms:
        - `b` - Baseline matching
        - `h` - Histogram matching
        - `s` - Spatial matching
        - `t` - Texture matching
        - `o` - Object detection

8. **Program Termination:**

    - Any other key will terminate the program.


## Contributing

Contributions are always welcome! If you would like to contribute:

- Fork the repository.
- Create your feature branch: `git checkout -b feature/YourFeature`
- Commit your changes: `git commit -m 'Add some feature'`
- Push to the branch: `git push origin feature/YourFeature`
- Open a pull request.

For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License

This project is licensed under the [MIT License]
