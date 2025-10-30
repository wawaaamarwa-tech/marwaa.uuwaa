#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

struct Nilai {
    float Mtk, BInd, BIng, IPA;
};

struct Siswa {
    string nama, nisn, jurusan;
    Nilai nilai;
};

void tambahData();
void tampilData();
void cariData();
void editData();
void hapusData();
void rankingSiswa();
float hitungAkhir(Nilai n);

int main() {
    int pilih;
    do {
        cout << "\n-------------------------------------\n";
        cout << "        PROGRAM DATA SISWA             \n";
        cout << "---------------------------------------\n";
        cout << "1. Tambah Data Siswa\n";
        cout << "2. Tampilkan Semua Data\n";
        cout << "3. Cari Data Siswa (NISN)\n";
        cout << "4. Edit Data Siswa\n";
        cout << "5. Hapus Data Siswa\n";
        cout << "6. Lihat Ranking Siswa\n";
        cout << "0. Keluar Program\n";
        cout << "-------------------------------------\n";
        cout << "Pilih Menu [0-6]: ";
        cin >> pilih;

        switch (pilih) {
            case 1: tambahData(); break;
            case 2: tampilData(); break;
            case 3: cariData(); break;
            case 4: editData(); break;
            case 5: hapusData(); break;
            case 6: rankingSiswa(); break;
            case 0: cout << "\nKeluar dari program...\n"; break;
            default: cout << "\nPilihan tidak valid, coba lagi!\n";
        }
    } while (pilih != 0);

    return 0;
}

void tambahData() {
    ofstream file("data_siswa.txt", ios::app);
    if (!file) {
        cout << "Gagal membuka file!\n";
        return;
    }

    Siswa s;
    cout << "\n--- INPUT DATA SISWA ---\n";
    cin.ignore();
    cout << "Nama Siswa   : "; getline(cin, s.nama);
    cout << "NISN         : "; getline(cin, s.nisn);
    cout << "Jurusan      : "; getline(cin, s.jurusan);
    cout << "Nilai Matematika       : "; cin >> s.nilai.Mtk;
    cout << "Nilai Bahasa Indonesia  : "; cin >> s.nilai.BInd;
    cout << "Nilai Bahasa Inggris    : "; cin >> s.nilai.BIng;
    cout << "Nilai IPA              : "; cin >> s.nilai.IPA;

    file << s.nama << "|" << s.nisn << "|" << s.jurusan << "|"
         << s.nilai.Mtk << " " << s.nilai.BInd << " "
         << s.nilai.BIng << " " << s.nilai.IPA << "\n";

    file.close();
    cout << "\n Data berhasil disimpan!\n";
}

float hitungAkhir(Nilai n) {
    return (0.4 * n.Mtk) + (0.3 * n.IPA) + (0.2 * n.BInd) + (0.1 * n.BIng);
}

void tampilData() {
    ifstream file("data_siswa.txt");
    if (!file) {
        cout << "\n File belum ada atau kosong!\n";
        return;
    }

    cout << "\n=== DAFTAR DATA SISWA ===\n";
    cout << left << setw(20) << "Nama"
         << setw(12) << "NISN"
         << setw(15) << "Jurusan"
         << setw(10) << "Mtk"
         << setw(10) << "B.Ind"
         << setw(10) << "B.Ing"
         << setw(10) << "IPA"
         << setw(10) << "Nil.Akhir" << endl;
    cout << string(85, '-') << endl;

    string line;
    Siswa s;
    while (getline(file, line)) {
        if (line.empty()) continue;
        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);
        s.nama = line.substr(0, p1);
        s.nisn = line.substr(p1 + 1, p2 - p1 - 1);
        s.jurusan = line.substr(p2 + 1, p3 - p2 - 1);
        sscanf(line.substr(p3 + 1).c_str(), "%f %f %f %f",
               &s.nilai.Mtk, &s.nilai.BInd, &s.nilai.BIng, &s.nilai.IPA);

        cout << left << setw(20) << s.nama
             << setw(12) << s.nisn
             << setw(15) << s.jurusan
             << setw(10) << s.nilai.Mtk
             << setw(10) << s.nilai.BInd
             << setw(10) << s.nilai.BIng
             << setw(10) << s.nilai.IPA
             << setw(10) << fixed << setprecision(2) << hitungAkhir(s.nilai)
             << endl;
    }

    file.close();
}

void cariData() {
    ifstream file("data_siswa.txt");
    if (!file) {
        cout << "\n File tidak ditemukan!\n";
        return;
    }

    string cari;
    cout << "\nMasukkan NISN yang ingin dicari: ";
    cin >> cari;

    string line;
    Siswa s;
    bool ketemu = false;

    while (getline(file, line)) {
        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);
        s.nama = line.substr(0, p1);
        s.nisn = line.substr(p1 + 1, p2 - p1 - 1);
        s.jurusan = line.substr(p2 + 1, p3 - p2 - 1);
        sscanf(line.substr(p3 + 1).c_str(), "%f %f %f %f",
               &s.nilai.Mtk, &s.nilai.BInd, &s.nilai.BIng, &s.nilai.IPA);

        if (s.nisn == cari) {
            ketemu = true;
            cout << "\n=== DATA DITEMUKAN ===\n";
            cout << "Nama     : " << s.nama << endl;
            cout << "Jurusan  : " << s.jurusan << endl;
            cout << "Nilai Akhir : " << hitungAkhir(s.nilai) << endl;
            break;
        }
    }

    if (!ketemu)
        cout << "\n Data dengan NISN " << cari << " tidak ditemukan!\n";

    file.close();
}

void editData() {
    ifstream file("data_siswa.txt");
    if (!file) {
        cout << "\nFile tidak ditemukan!\n";
        return;
    }

    vector<Siswa> list;
    string line;
    Siswa s;
    while (getline(file, line)) {
        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);
        s.nama = line.substr(0, p1);
        s.nisn = line.substr(p1 + 1, p2 - p1 - 1);
        s.jurusan = line.substr(p2 + 1, p3 - p2 - 1);
        sscanf(line.substr(p3 + 1).c_str(), "%f %f %f %f",
               &s.nilai.Mtk, &s.nilai.BInd, &s.nilai.BIng, &s.nilai.IPA);
        list.push_back(s);
    }
    file.close();

    string target;
    cout << "\nMasukkan NISN yang ingin diedit: ";
    cin >> target;
    bool found = false;

    for (auto &x : list) {
        if (x.nisn == target) {
            found = true;
            cout << "\nData ditemukan. Masukkan data baru.\n";
            cin.ignore();
            cout << "Nama baru (" << x.nama << "): ";
            getline(cin, x.nama);
            cout << "Jurusan baru (" << x.jurusan << "): ";
            getline(cin, x.jurusan);
            cout << "Nilai Mtk  : "; cin >> x.nilai.Mtk;
            cout << "Nilai B.Ind: "; cin >> x.nilai.BInd;
            cout << "Nilai B.Ing: "; cin >> x.nilai.BIng;
            cout << "Nilai IPA  : "; cin >> x.nilai.IPA;
            break;
        }
    }

    if (!found) {
        cout << "\n NISN tidak ditemukan!\n";
        return;
    }

    ofstream out("data_siswa.txt");
    for (auto &x : list) {
        out << x.nama << "|" << x.nisn << "|" << x.jurusan << "|"
            << x.nilai.Mtk << " " << x.nilai.BInd << " "
            << x.nilai.BIng << " " << x.nilai.IPA << "\n";
    }
    out.close();
    cout << "\n Data berhasil diperbarui!\n";
}


void hapusData() {
    ifstream file("data_siswa.txt");
    if (!file) {
        cout << "\n❌ File tidak ditemukan!\n";
        return;
    }

    vector<Siswa> list;
    string line;
    Siswa s;
    while (getline(file, line)) {
        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);
        s.nama = line.substr(0, p1);
        s.nisn = line.substr(p1 + 1, p2 - p1 - 1);
        s.jurusan = line.substr(p2 + 1, p3 - p2 - 1);
        sscanf(line.substr(p3 + 1).c_str(), "%f %f %f %f",
               &s.nilai.Mtk, &s.nilai.BInd, &s.nilai.BIng, &s.nilai.IPA);
        list.push_back(s);
    }
    file.close();

    string target;
    cout << "\nMasukkan NISN yang ingin dihapus: ";
    cin >> target;

    ofstream out("data_siswa.txt");
    bool deleted = false;
    for (auto &x : list) {
        if (x.nisn != target)
            out << x.nama << "|" << x.nisn << "|" << x.jurusan << "|"
                << x.nilai.Mtk << " " << x.nilai.BInd << " "
                << x.nilai.BIng << " " << x.nilai.IPA << "\n";
        else
            deleted = true;
    }
    out.close();

    if (deleted)
        cout << "\n Data berhasil dihapus!\n";
    else
        cout << "\n NISN tidak ditemukan!\n";
}

void rankingSiswa() {
    ifstream file("data_siswa.txt");
    if (!file) {
        cout << "\n File tidak ditemukan!\n";
        return;
    }

    vector<Siswa> list;
    Siswa s;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);
        s.nama = line.substr(0, p1);
        s.nisn = line.substr(p1 + 1, p2 - p1 - 1);
        s.jurusan = line.substr(p2 + 1, p3 - p2 - 1);
        sscanf(line.substr(p3 + 1).c_str(), "%f %f %f %f",
               &s.nilai.Mtk, &s.nilai.BInd, &s.nilai.BIng, &s.nilai.IPA);
        list.push_back(s);
    }
    file.close();

    sort(list.begin(), list.end(), [](Siswa a, Siswa b) {
        return hitungAkhir(a.nilai) > hitungAkhir(b.nilai);
    });

    cout << "\n=== RANKING SISWA ===\n";
    cout << left << setw(5) << "No"
         << setw(20) << "Nama"
         << setw(12) << "NISN"
         << setw(15) << "Jurusan"
         << setw(10) << "Nil.Akhir" << endl;
    cout << string(65, '-') << endl;

    int no = 1;
    for (auto &x : list) {
        cout << left << setw(5) << no++
             << setw(20) << x.nama
             << setw(12) << x.nisn
             << setw(15) << x.jurusan
             << setw(10) << fixed << setprecision(2)
             << hitungAkhir(x.nilai) << endl;
    }
}
