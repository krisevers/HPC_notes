struct Parameters
{
    double E_Na;   // Sodium reversal potential (mV)
    double g_Na;   // Sodium conductance (mS/cm^2)
    double E_K;    // Potassium reversal potential (mV)
    double g_K;    // Potassium conductance (mS/cm^2)
    double E_L;    // Leak reversal potential (mV)
    double g_L;    // Leak conductance (mS/cm^2)
    double C_m;    // Membrane capacitance (uF/cm^2)
    double V_rest; // Resting membrane potential (mV)
};

struct State
{
    double V; // Membrane potential (mV)
    double n; // Potassium activation
    double m; // Sodium activation
    double h; // Sodium inactivation
};

// Hodgkin-Huxley gating variable rate functions
double alpha_n(double V)
{
    return 0.01 * (V + 55.0) / (1.0 - exp(-(V + 55.0) / 10.0));
}

double beta_n(double V)
{
    return 0.125 * exp(-(V + 65.0) / 80.0);
}

double alpha_m(double V)
{
    return 0.1 * (V + 40.0) / (1.0 - exp(-(V + 40.0) / 10.0));
}

double beta_m(double V)
{
    return 4.0 * exp(-(V + 65.0) / 18.0);
}

double alpha_h(double V)
{
    return 0.07 * exp(-(V + 65.0) / 20.0);
}

double beta_h(double V)
{
    return 1.0 / (1.0 + exp(-(V + 35.0) / 10.0));
}

// Compute derivatives for the Hodgkin-Huxley model
void dX(const struct Parameters *p, const struct State *s, double I_ext,
        double *dV, double *dn, double *dm, double *dh)
{
    double V = s->V;
    double n = s->n;
    double m = s->m;
    double h = s->h;

    double I_Na = p->g_Na * pow(m, 3) * h * (V - p->E_Na);
    double I_K = p->g_K * pow(n, 4) * (V - p->E_K);
    double I_L = p->g_L * (V - p->E_L);

    *dV = (I_ext - I_Na - I_K - I_L) / p->C_m;
    *dn = alpha_n(V) * (1.0 - n) - beta_n(V) * n;
    *dm = alpha_m(V) * (1.0 - m) - beta_m(V) * m;
    *dh = alpha_h(V) * (1.0 - h) - beta_h(V) * h;
}

void rk4_step(const struct Parameters *p, struct State *s, double I_ext, double dt)
{
    double dV1, dn1, dm1, dh1;
    double dV2, dn2, dm2, dh2;
    double dV3, dn3, dm3, dh3;
    double dV4, dn4, dm4, dh4;

    struct State tmp = *s;

    // k1
    dX(p, s, I_ext, &dV1, &dn1, &dm1, &dh1);

    // k2
    tmp.V = s->V + 0.5 * dt * dV1;
    tmp.n = s->n + 0.5 * dt * dn1;
    tmp.m = s->m + 0.5 * dt * dm1;
    tmp.h = s->h + 0.5 * dt * dh1;
    dX(p, &tmp, I_ext, &dV2, &dn2, &dm2, &dh2);

    // k3
    tmp.V = s->V + 0.5 * dt * dV2;
    tmp.n = s->n + 0.5 * dt * dn2;
    tmp.m = s->m + 0.5 * dt * dm2;
    tmp.h = s->h + 0.5 * dt * dh2;
    dX(p, &tmp, I_ext, &dV3, &dn3, &dm3, &dh3);

    // k4
    tmp.V = s->V + dt * dV3;
    tmp.n = s->n + dt * dn3;
    tmp.m = s->m + dt * dm3;
    tmp.h = s->h + dt * dh3;
    dX(p, &tmp, I_ext, &dV4, &dn4, &dm4, &dh4);

    s->V += (dt / 6.0) * (dV1 + 2.0 * dV2 + 2.0 * dV3 + dV4);
    s->n += (dt / 6.0) * (dn1 + 2.0 * dn2 + 2.0 * dn3 + dn4);
    s->m += (dt / 6.0) * (dm1 + 2.0 * dm2 + 2.0 * dm3 + dm4);
    s->h += (dt / 6.0) * (dh1 + 2.0 * dh2 + 2.0 * dh3 + dh4);
}

void simulate(const struct Parameters *p, struct State *s, double I_ext,
              double t_end, double dt,
              void (*callback)(double t, const struct State *s, void *user), void *user)
{
    double t = 0.0;
    while (t < t_end)
    {
        if (callback)
            callback(t, s, user);
        rk4_step(p, s, I_ext, dt);
        t += dt;
    }
    if (callback)
        callback(t, s, user);
}
