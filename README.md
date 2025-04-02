# 🛠️ Unity PDB Drainer

![Unity PDB Drainer](Assets/banner_1200x400.png)

🚀 **Unity PDB Drainer** is a lightweight Windows specified command-line tool that automatically downloads Program Database (PDB) files from the official **Unity Symbols Server**.
Use it for **debugging, analysis, and reverse engineering** Unity applications!

---

## ✨ Features

✔ **Simple CLI Interface** – One-time execution without complex setup.  
✔ **Automatic Download** – Fetches and extracts PDB files within seconds.  
✔ **Extensible** – Easily modify it to support additional symbol sources.  

---

## 📦 Installation

### **1️⃣ Pre-Built Release (Recommended)**
📅 **Download the latest release** from the [Releases section](https://github.com/yourusername/unity-pdb-drainer/releases) and run it instantly!

### **2️⃣ Build from Source**
**🔹 Requirements:**  
- If you want to **build the project manually**, install [Visual Studio](https://visualstudio.microsoft.com/vs/).  
- You also need [vcpkg](https://github.com/microsoft/vcpkg).  

#### **Steps:**  
```bash
# Clone the repository
git clone https://github.com/yourusername/unity-pdb-drainer.git
cd unity-pdb-drainer

# Install dependencies using vcpkg
vcpkg install spdlog:x64-windows
```

---

## 🚀 Usage
Run the tool by specifying the file path:  
```bash
PDBDrainer.exe <YourFilePath>
```
Example:  
```bash
PDBDrainer.exe mono-2.0-bdwgc.dll
```

**💌 Sample Output:**
```
[19:59:42.464] [info] [Welcome to Unity PDB Drainer!]

[19:59:42.465] [info] Opening File: mono-2.0-bdwgc.dll
[19:59:42.472] [info] File size: 7895744
[19:59:42.479] [info] Packed PDB URL: http://symbolserver.unity3d.com/mono-2.0-bdwgc.pdb/84118EDF9E7A43D6B39AAD583715AA2F1/mono-2.0-bdwgc.pdb
[19:59:42.479] [info] Downloading file...
[19:59:43.916] [info] Successfully downloaded file
[19:59:43.919] [info] I am unpacking PDB right now, it may take a while...
[19:59:44.095] [info] We are done, but I need to delete packed pdb and do some cleanup, wait a sec...
[19:59:44.096] [info] Packed PDB deleted successfully.
[19:59:44.097] [info] Finished, have a nice day!
[19:59:44.097] [info] Press enter to leave...
```

---

## 💡 Contributing
🎯 Want to contribute? Awesome!

1. **Fork the repository**  
2. **Create a new branch** (`git checkout -b feature-name`)  
3. **Make your changes**  
4. **Submit a pull request**  

All contributions are welcome! 😊  

---

## 🐝 License
This project is licensed under the **MIT License**. See [LICENSE](LICENSE) for details.

---

## 📩 Contact
💬 Have questions or suggestions? Open an **Issue** in the repository!

🌟 Thanks for using **Unity PDB Drainer**! Happy debugging! 🎮🚀

