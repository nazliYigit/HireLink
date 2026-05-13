using System;
using System.Windows.Forms;
using System.Drawing;

namespace IsIlani
{
    public class FormKayit : Form
    {
        private TabControl tabCtrl;

        // İş Arayan alanları
        private TextBox txtTC, txtAd, txtSoyad, txtAdres, txtTel, txtEmail, txtDogum;
        // Şirket alanları
        private TextBox txtSirketNo, txtSirketAd, txtSirketAdres, txtSirketTel, txtSirketEmail;

        public FormKayit()
        {
            Text            = "Kayıt İşlemleri";
            Size            = new Size(520, 480);
            StartPosition   = FormStartPosition.CenterScreen;
            FormBorderStyle = FormBorderStyle.FixedSingle;
            MaximizeBox     = false;
            BackColor       = Color.FromArgb(245, 248, 255);
            BuildUI();
        }

        private void BuildUI()
        {
            tabCtrl = new TabControl { Dock = DockStyle.Fill, Font = new Font("Segoe UI", 10) };

            tabCtrl.TabPages.Add(TabIsArayan());
            tabCtrl.TabPages.Add(TabSirket());

            Controls.Add(tabCtrl);
        }

        // ─── İş Arayan Sekmesi ────────────────────────────────────────────
        private TabPage TabIsArayan()
        {
            var page = new TabPage("İş Arayan Kaydı");
            int y = 20;

            txtTC     = Alan(page, "TC Kimlik No (11 hane):", ref y);
            txtAd     = Alan(page, "Ad:", ref y);
            txtSoyad  = Alan(page, "Soyad:", ref y);
            txtAdres  = Alan(page, "Adres:", ref y);
            txtTel    = Alan(page, "Telefon:", ref y);
            txtEmail  = Alan(page, "E-posta:", ref y);
            txtDogum  = Alan(page, "Doğum Tarihi (YYYY-MM-DD):", ref y);

            var btnKaydet = new Button
            {
                Text      = "Kaydet",
                Location  = new Point(180, y + 10),
                Size      = new Size(140, 40),
                Font      = new Font("Segoe UI", 11, FontStyle.Bold),
                BackColor = Color.FromArgb(52, 120, 200),
                ForeColor = Color.White,
                FlatStyle = FlatStyle.Flat
            };
            btnKaydet.Click += BtnIsArayanKaydet_Click;
            page.Controls.Add(btnKaydet);
            return page;
        }

        private void BtnIsArayanKaydet_Click(object sender, EventArgs e)
        {
            string tc = txtTC.Text.Trim();
            if (tc.Length != 11 || !long.TryParse(tc, out _))
            {
                Msg("TC kimlik numarası 11 haneli rakam olmalıdır.", true); return;
            }
            if (string.IsNullOrWhiteSpace(txtAd.Text) || string.IsNullOrWhiteSpace(txtSoyad.Text))
            {
                Msg("Ad ve soyad boş olamaz.", true); return;
            }

            int sonuc = Backend.ia_ekle(tc,
                txtAd.Text.Trim(), txtSoyad.Text.Trim(),
                txtAdres.Text.Trim(), txtTel.Text.Trim(),
                txtEmail.Text.Trim(), txtDogum.Text.Trim());

            if (sonuc == 1)  { Msg("İş arayan başarıyla kaydedildi."); TemizleIA(); }
            else if (sonuc == -1) Msg("Bu TC ile kayıt zaten mevcut.", true);
            else                  Msg("Kayıt sırasında hata oluştu.", true);
        }

        // ─── Şirket Sekmesi ───────────────────────────────────────────────
        private TabPage TabSirket()
        {
            var page = new TabPage("Şirket Kaydı");
            int y = 20;

            txtSirketNo    = Alan(page, "Şirket No:", ref y);
            txtSirketAd    = Alan(page, "Şirket Adı:", ref y);
            txtSirketAdres = Alan(page, "Adres:", ref y);
            txtSirketTel   = Alan(page, "Telefon:", ref y);
            txtSirketEmail = Alan(page, "E-posta:", ref y);

            var btnKaydet = new Button
            {
                Text      = "Kaydet",
                Location  = new Point(180, y + 10),
                Size      = new Size(140, 40),
                Font      = new Font("Segoe UI", 11, FontStyle.Bold),
                BackColor = Color.FromArgb(34, 140, 100),
                ForeColor = Color.White,
                FlatStyle = FlatStyle.Flat
            };
            btnKaydet.Click += BtnSirketKaydet_Click;
            page.Controls.Add(btnKaydet);
            return page;
        }

        private void BtnSirketKaydet_Click(object sender, EventArgs e)
        {
            if (!int.TryParse(txtSirketNo.Text.Trim(), out int no))
            {
                Msg("Şirket no sayısal olmalıdır.", true); return;
            }
            if (string.IsNullOrWhiteSpace(txtSirketAd.Text))
            {
                Msg("Şirket adı boş olamaz.", true); return;
            }

            int sonuc = Backend.sirket_ekle_api(no,
                txtSirketAd.Text.Trim(), txtSirketAdres.Text.Trim(),
                txtSirketTel.Text.Trim(), txtSirketEmail.Text.Trim());

            if (sonuc == 1)  { Msg("Şirket başarıyla kaydedildi."); TemizleSirket(); }
            else if (sonuc == -1) Msg("Bu şirket no ile kayıt zaten mevcut.", true);
            else                  Msg("Kayıt sırasında hata oluştu.", true);
        }

        // ─── Yardımcı ─────────────────────────────────────────────────────
        private TextBox Alan(TabPage page, string etiket, ref int y)
        {
            var lbl = new Label { Text = etiket, Location = new Point(20, y), AutoSize = true,
                                  Font = new Font("Segoe UI", 9) };
            var txt = new TextBox { Location = new Point(220, y - 2), Size = new Size(250, 24),
                                    Font = new Font("Segoe UI", 10) };
            page.Controls.AddRange(new Control[] { lbl, txt });
            y += 38;
            return txt;
        }

        private void Msg(string mesaj, bool hata = false) =>
            MessageBox.Show(mesaj, hata ? "Hata" : "Bilgi",
                MessageBoxButtons.OK, hata ? MessageBoxIcon.Warning : MessageBoxIcon.Information);

        private void TemizleIA() { txtTC.Clear(); txtAd.Clear(); txtSoyad.Clear();
                                   txtAdres.Clear(); txtTel.Clear(); txtEmail.Clear(); txtDogum.Clear(); }
        private void TemizleSirket() { txtSirketNo.Clear(); txtSirketAd.Clear();
                                       txtSirketAdres.Clear(); txtSirketTel.Clear(); txtSirketEmail.Clear(); }
    }
}
