import java.util.Objects;

public class NhanVien {
    private String maNhanVien;
    private String ho;
    private String ten;
    private String phai;
    private int tuoi;
    private double tienLuong;

    public NhanVien() {
    }

    public NhanVien(String maNhanVien, String ho, String ten, String phai, int tuoi, double tienLuong) {
        setMaNhanVien(maNhanVien);
        setHo(ho);
        setTen(ten);
        setPhai(phai);
        setTuoi(tuoi);
        setTienLuong(tienLuong);
    }

    public String getMaNhanVien() {
        return maNhanVien;
    }

    public void setMaNhanVien(String maNhanVien) {
        if (maNhanVien == null || maNhanVien.trim().isEmpty()) {
            throw new IllegalArgumentException("Mã nhân viên không được rỗng.");
        }
        this.maNhanVien = maNhanVien.trim();
    }

    public String getHo() {
        return ho;
    }

    public void setHo(String ho) {
        if (ho == null || ho.trim().isEmpty()) {
            throw new IllegalArgumentException("Họ không được rỗng.");
        }
        this.ho = ho.trim();
    }

    public String getTen() {
        return ten;
    }

    public void setTen(String ten) {
        if (ten == null || ten.trim().isEmpty()) {
            throw new IllegalArgumentException("Tên không được rỗng.");
        }
        this.ten = ten.trim();
    }

    public String getPhai() {
        return phai;
    }

    public void setPhai(String phai) {
        if (phai == null || phai.trim().isEmpty()) {
            throw new IllegalArgumentException("Phái không được rỗng.");
        }
        String normalized = phai.trim();
        if (!normalized.equalsIgnoreCase("Nam") && !normalized.equalsIgnoreCase("Nữ")) {
            throw new IllegalArgumentException("Phái chỉ nhận 'Nam' hoặc 'Nữ'.");
        }
        this.phai = normalized.substring(0, 1).toUpperCase() + normalized.substring(1).toLowerCase();
    }

    public int getTuoi() {
        return tuoi;
    }

    public void setTuoi(int tuoi) {
        if (tuoi <= 0) {
            throw new IllegalArgumentException("Tuổi phải lớn hơn 0.");
        }
        this.tuoi = tuoi;
    }

    public double getTienLuong() {
        return tienLuong;
    }

    public void setTienLuong(double tienLuong) {
        if (tienLuong < 0) {
            throw new IllegalArgumentException("Tiền lương không được âm.");
        }
        this.tienLuong = tienLuong;
    }

    public String getHoTen() {
        return ho + " " + ten;
    }

    @Override
    public String toString() {
        return "NhanVien{" +
                "maNhanVien='" + maNhanVien + '\'' +
                ", ho='" + ho + '\'' +
                ", ten='" + ten + '\'' +
                ", phai='" + phai + '\'' +
                ", tuoi=" + tuoi +
                ", tienLuong=" + tienLuong +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof NhanVien)) return false;
        NhanVien nhanVien = (NhanVien) o;
        return maNhanVien.equalsIgnoreCase(nhanVien.maNhanVien);
    }

    @Override
    public int hashCode() {
        return Objects.hash(maNhanVien.toLowerCase());
    }
}
