#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

struct siswa {
    string nama;
    string nisn;
    string jurusan;
    float nilaiMtk;
    float nilaiBindo;
    float nilaiIpa;
};

int main(){
    siswa s;

    cout << "=== INPUT DATA SISWA ===" << endl;
    cout << "Masukkan Nama: ";
    getline(cin, s.nama);
    cout << "Masukkan NISN: ";
    cin >> s.nisn;
    cout << "Masukkan Jurusan: ";
    cin.ignore(); 
    getline(cin, s.jurusan);
    cout << "Masukkan Nilai Matematika: ";
    cin >> s.nilaiMtk;
    cout << "Masukkan Nilai Bahasa Indonesia: ";
    cin >> s.nilaiBindo;
    cout << "Masukkan Nilai IPA: ";
    cin >> s.nilaiIpa;

    float rata = (s.nilaiMtk + s.nilaiBindo + s.nilaiIpa) / 3;

    cout << endl;
    cout << "=== DATA SISWA ===" << endl;
    cout << "nama    : " << s.nama << endl;
    cout << "nisn   : " << s.nisn << endl;
    cout << "jurusan : " << s.jurusan << endl;
    cout << "nilai Rata-rata : " << rata << endl;

    if (rata >= 75){
        cout << "Keterangan : Lulus" << endl;
    } else {
        cout << "Keterangan : Tidak Lulus" << endl;
    }

    return 0;
}
