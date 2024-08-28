# ArchiveCrack

Brute Force Password Cracker for Local Archive Files.

This project is a command-line tool designed to perform brute force attacks on local archive files to uncover password-protected content. It systematically tests all possible combinations of passwords to find the correct one. 

The tool is capable of handling various archive formats supported by 7-Zip and is designed to work efficiently on local files.

# Key Features

Password Cracking: Automatically tests a wide range of passwords to gain access to protected archives.

Archive Compatibility: Works with multiple archive formats supported by 7-Zip.

Progress Feedback: Provides real-time feedback on the progress of the password testing.

# Usage
```
archivecrack <ArchiveFile.Format>
```

Provide the path to the archive file as a command-line argument.

The tool generates and tests possible passwords until the correct one is found or all options are exhausted.

# Install
```
makedepends={gcc}
depends={7zip}
```
How to build and install?

```
git clone https://github.com/moskensoap/archivecrack.git
cd archivecrack
make
```
Then, copy the executable `archivecrack` to a directory in PATH.