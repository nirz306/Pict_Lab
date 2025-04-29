# Setting Up KVM on Ubuntu

This guide provides the necessary commands to install and run KVM (Kernel-based Virtual Machine) on an Ubuntu system. Each command is explained briefly with expected outcomes.

## 1. Update Package Lists
```bash
sudo apt update
```
**Purpose:** Updates local package index.
**Expected Output:** List of updated packages.

## 2. Check CPU Virtualization Support
```bash
egrep -c '(vmx|svm)' /proc/cpuinfo
```
**Purpose:** Checks if CPU supports virtualization (Intel VT-x or AMD-V).
**Expected Output:** A number ≥1 indicates support.

## 3. Verify KVM Support
```bash
sudo kvm-ok
```
**Purpose:** Confirms if KVM can be used.
**Expected Output:** Message like "KVM acceleration can be used."

## 4. Install CPU Checker
```bash
sudo apt install cpu-checker
```
**Purpose:** Installs `kvm-ok` utility.
**Expected Output:** Successful installation message.

## 5. Install KVM and Dependencies
```bash
sudo apt install qemu-kvm libvirt-daemon-system libvirt-clients bridge-utils -y
```
**Purpose:** Installs KVM, libvirt and networking tools.
**Expected Output:** Packages installed without errors.

## 6. Add User to libvirt Group
```bash
sudo adduser [username] libvirt
```
**Purpose:** Grants user permissions to manage VMs.
**Expected Output:** Confirmation that the user was added.

## 7. Add User to kvm Group
```bash
sudo adduser [username] kvm
```
**Purpose:** Grants user access to KVM.
**Expected Output:** Confirmation that the user was added.

## 8. List All VMs
```bash
sudo virsh list --all
```
**Purpose:** Lists existing virtual machines.
**Expected Output:** A table listing VMs (or empty if none exist).

## 9. Check libvirtd Service Status
```bash
sudo systemctl status libvirtd
```
**Purpose:** Checks if the libvirt daemon is running.
**Expected Output:** Active (running) service status.

## 10. Enable and Start libvirtd Service
```bash
sudo systemctl enable --now libvirtd
```
**Purpose:** Enables and starts the libvirt daemon immediately.
**Expected Output:** Service enabled and active.

## 11. Install Virt-Manager
```bash
sudo apt install virt-manager -y
```
**Purpose:** Installs a GUI tool for managing virtual machines.
**Expected Output:** Packages installed without errors.

## 12. Launch Virt-Manager
```bash
sudo virt-manager
```
**Purpose:** Starts the Virt-Manager GUI.
**Expected Output:** Virt-Manager window opens to manage VMs.

---

**Note:** After adding the user to groups, you may need to log out and log back in for changes to take effect.

