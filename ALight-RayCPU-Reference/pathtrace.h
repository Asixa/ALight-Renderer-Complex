vec3 Engine::pathtrace(const Ray &r, int n)
{
    // Immediately return vec3(0) if recursion limit was hit
    if (n > RECURSION_MAX)
        return COLOR_NULL;

    // Initialize all pathtracing data
    auto radiance = vec3();

    // Find the closest intersection
    auto xFinal = intersect(r, MAXDISTANCE);

    // Return black if no intersection happened
    if (xFinal == invalidIntersection)
        return COLOR_NULL;

    // Return the emittance immediately if we hit an emissive surface
    if (xFinal.getMaterial().getEmittance().length() > 0.0f)
    {
        return xFinal.getMaterial().getEmittance();
    }

    // Assign intersection data into shorter variable names for easier use
    auto V_vector = r.GetDirection();
    auto P_vector = xFinal.getPosition();
    auto N_vector = xFinal.getNormal();
    auto Nr_vector = vec3::dot(N_vector, V_vector) < 0.0f ? N_vector : N_vector.negate();
    auto M_info = xFinal.getMaterial();
    auto f = M_info.getReflectance();

    // Russian roulette, use maximum reflectance amount
    auto p = f.x > f.y && f.x > f.z ? f.x : f.y > f.z ? f.y : f.z;
    if (n > RECURSION_MAX/2 || !p)
        if (math::pseudorand() < p)
            f *= (1.0f / p);

    // Diffuse surfaces
    if (M_info.getReflT() == DIFF)
    {
        // Calculate the light direction ray
        auto L_rand = vec3::sampleHemisphere(N_vector);

        // Prepare all required information
        auto L_vector = L_rand.negate();

        // Calculate all dot products
        auto NdotL = std::abs(vec3::dot(N_vector, L_vector));

        // Calculate the bidirectional reflectance function value
        auto BRDF = 2.0f * NdotL * PI_1;

        // Get the reflected light amount from L_rand
        auto REFL = pathtrace(Ray(P_vector, L_rand), n + 1);

        // Return the final radiance
        return f * BRDF * REFL;
    }
    // Glossy specular surfaces (Cook-torrance microfacet brdf model)
    // TODO: Fix fireflies caused by really low roughness values
    else if (M_info.getReflT() == GLOS)
    {
        // Get the random hemisphere and mirror reflection directions
        auto L_mirr = vec3::reflect(V_vector, N_vector).normalize();
        auto L_rand = vec3::sampleHemisphere(L_mirr); // Normal plane is perpendicular to the mirror reflection

        // Check if the reflected ray aims through the surface, if true reflect against the normal plane
        if (vec3::dot(N_vector, L_rand) < 0.0f)
            L_rand = vec3::reflect(L_rand, L_mirr).normalize();

        // Temp surface values
        float R = M_info.getRoughness();
        float RR = R * R;
        float F = M_info.getFresnel();
        float K = M_info.getDensity();

        // Prepare all required information
        auto L_vector = L_rand.negate();
        auto H_vector = (V_vector + L_vector).normalize();

        // Calculate all dot products
        auto NdotL = std::abs(vec3::dot(N_vector, L_vector));
        auto NdotV = std::abs(vec3::dot(N_vector, V_vector));
        auto NdotH = std::abs(vec3::dot(N_vector, H_vector));
        auto VdotH = std::abs(vec3::dot(V_vector, H_vector));

        // Evaluate the geometric term
        float geo_numer = 2.0f * NdotH;
        float geo_denom = VdotH;
        float geo = std::min(1.0f, std::min((geo_numer * NdotV) / geo_denom, (geo_numer * NdotL) / geo_denom));

        // Evaluate the roughness term
        float rough_a = 1.0f / (4.0f * RR * std::pow(NdotH, 4.0f));
        float rough_b = NdotH * NdotH - 1.0f;
        float rough_c = RR * NdotH * NdotH;
        float rough = rough_a * std::exp(rough_b / rough_c);

        // Evaluate the fresnel term
        float fresnel = std::pow(1.0f - VdotH, 5.0f);
        fresnel *= 1.0f - F;
        fresnel += F;

        // Put the terms together
        float Rs = geo * rough * fresnel / (PI * NdotV * NdotL + EPSILON); // <-- Still unsure about this

        // Calculate the cook-torrance brdf value
        auto BRDF = 2.0f * NdotL * (Rs * (1.0f - K) + K); // <-- Still unsure about this as well

        // Get the reflected light amount from L_rand
        auto REFL = pathtrace(Ray(P_vector, L_rand), n + 1);

        // Return the final radiance
        return f * BRDF * REFL;
    }
    // Mirror surfaces
    else if (M_info.getReflT() == SPEC)
    {
        return f * pathtrace(Ray(P_vector, vec3::reflect(V_vector, N_vector)), n + 1);
    }
    // Dielectric surfaces, taken nearly directly from the smallpt powerpoint presentation, because it is so good and accurate.
    else if (M_info.getReflT() == REFR)
    {
        auto r_reflected = Ray(P_vector, vec3::reflect(V_vector, N_vector));
        auto into = vec3::dot(N_vector, Nr_vector) > 0.0f;
        float nc = 1, nt = M_info.getIOR(), nnt = into ? nc / nt : nt / nc, ddn = vec3::dot(V_vector, Nr_vector), cos2t;

        // If total internal reflection, reflect
        if ((cos2t = 1.0f - nnt * nnt * (1.0f - ddn * ddn)) < 0.0f)
            return f * pathtrace(r_reflected, n + 1);

        // Otherwise, choose reflection or refraction
        auto tdir = (V_vector * nnt - N_vector * ((into ? 1.0f : -1.0f) * (ddn * nnt + std::sqrt(cos2t)))).normalize();
        auto a = nt - nc, b = nt + nc, R0 = a * a / (b * b), c = 1.0f - (into ? -ddn : vec3::dot(tdir, N_vector));
        auto Re = R0 + (1.0f - R0) * c * c * c * c * c, Tr = 1.0f - Re, P = 0.25f + 0.5f * Re, RP = Re / P, TP = Tr / (1.0f - P);
        return f * (n > 2 ? (math::pseudorand() < P ?
                             pathtrace(r_reflected, n + 1) * RP : pathtrace(Ray(P_vector, tdir), n + 1) * TP):
                    pathtrace(r_reflected, n + 1) * Re + pathtrace(Ray(P_vector, tdir), n + 1) * Tr);
    }

    return radiance;
}
