import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class DanhSachNhanVien {
    private final List<NhanVien> danhSach;

    public DanhSachNhanVien() {
        this.danhSach = new ArrayList<>();
    }

    public List<NhanVien> getTatCa() {
        return Collections.unmodifiableList(danhSach);
    }

    public int size() {
        return danhSach.size();
    }

    public boolean themNhanVien(NhanVien nhanVien) {
        if (nhanVien == null) {
            throw new IllegalArgumentException("Nhân viên không được null.");
        }
        if (timTheoMa(nhanVien.getMaNhanVien()) != null) {
            return false;
        }
        return danhSach.add(nhanVien);
    }

    public NhanVien timTheoMa(String maNhanVien) {
        if (maNhanVien == null || maNhanVien.trim().isEmpty()) {
            return null;
        }
        for (NhanVien nv : danhSach) {
            if (nv.getMaNhanVien().equalsIgnoreCase(maNhanVien.trim())) {
                return nv;
            }
        }
        return null;
    }

    public List<NhanVien> timTheoTen(String keyword) {
        List<NhanVien> ketQua = new ArrayList<>();
        if (keyword == null) {
            return ketQua;
        }
        String tuKhoa = keyword.trim().toLowerCase();
        for (NhanVien nv : danhSach) {
            String hoTen = nv.getHoTen().toLowerCase();
            if (hoTen.contains(tuKhoa)) {
                ketQua.add(nv);
            }
        }
        return ketQua;
    }

    public boolean xoaTheoMa(String maNhanVien) {
        NhanVien nv = timTheoMa(maNhanVien);
        if (nv == null) {
            return false;
        }
        return danhSach.remove(nv);
    }

    public boolean capNhatNhanVien(String maNhanVien, NhanVien thongTinMoi) {
        if (thongTinMoi == null) {
            throw new IllegalArgumentException("Thông tin mới không được null.");
        }
        NhanVien nvCu = timTheoMa(maNhanVien);
        if (nvCu == null) {
            return false;
        }

        // Không cho đổi mã thành mã đã tồn tại của nhân viên khác.
        NhanVien tonTai = timTheoMa(thongTinMoi.getMaNhanVien());
        if (tonTai != null && tonTai != nvCu) {
            return false;
        }

        nvCu.setMaNhanVien(thongTinMoi.getMaNhanVien());
        nvCu.setHo(thongTinMoi.getHo());
        nvCu.setTen(thongTinMoi.getTen());
        nvCu.setPhai(thongTinMoi.getPhai());
        nvCu.setTuoi(thongTinMoi.getTuoi());
        nvCu.setTienLuong(thongTinMoi.getTienLuong());
        return true;
    }

    public void xoaTrang() {
        danhSach.clear();
    }
}
