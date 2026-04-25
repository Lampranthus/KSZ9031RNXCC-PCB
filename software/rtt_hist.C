/*
 * rtt_hist.C
 * Uso: root -l 'rtt_hist.C("archivo.csv")'
 */

void rtt_hist(const char *fname = "rtt.csv")
{
    gSystem->Load("libHist.so");
    gSystem->Load("libGraf.so");
    gSystem->Load("libGpad.so");

    /* Leer CSV */
    std::vector<double> rtts;
    FILE *f = fopen(fname, "r");
    if (!f) { printf("No se pudo abrir %s\n", fname); return; }

    char line[256];
    fgets(line, sizeof(line), f);   /* saltar cabecera */
    uint64_t timeouts = 0;
    while (fgets(line, sizeof(line), f)) {
        unsigned seq;
        double rtt;
        char status[32];
        if (sscanf(line, "%u,%lf,%31s", &seq, &rtt, status) == 3)
            rtts.push_back(rtt);
        else
            timeouts++;
    }
    fclose(f);

    if (rtts.empty()) { printf("Sin datos.\n"); return; }

    /* Rango */
    double vmin = *std::min_element(rtts.begin(), rtts.end());
    double vmax = *std::max_element(rtts.begin(), rtts.end());
    double margin = (vmax - vmin) * 0.05;

    TH1D *h = new TH1D("h", fname, 100, vmin - margin, vmax + margin);
    for (double v : rtts) h->Fill(v);

    TCanvas *c = new TCanvas("c", "RTT", 900, 600);
    h->GetXaxis()->SetTitle("RTT (#mus)");
    h->GetYaxis()->SetTitle("Cuentas");
    h->Draw();
    c->SaveAs("rtt_histogram.png");

    printf("N=%zu  min=%.1f  max=%.1f  timeouts=%llu\n",
           rtts.size(), vmin, vmax, (unsigned long long)timeouts);
}
