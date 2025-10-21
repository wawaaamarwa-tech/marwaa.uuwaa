##include <iostream>
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
    siswa s;  // bikin 1 data siswa

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
    cout << "Nama    : " << s.nama << endl;
    cout << "NISN    : " << s.nisn << endl;
    cout << "Jurusan : " << s.jurusan << endl;
    cout << "Nilai Rata-rata : " << rata << endl;

    if (rata >= 75){
        cout << "Keterangan : Lulus" << endl;
    } else {
        cout << "Keterangan : Tidak Lulus" << endl;
    }

    return 0;
}
