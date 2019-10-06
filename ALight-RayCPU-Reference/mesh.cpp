#include "mesh.h"

Mesh::Mesh(const char *fileName, Material material)
{
    m_fileName = fileName;
    m_material = material;

    if (loadObj() != 0)
    {
        std::cerr << "Mesh: Error loading " << m_fileName << std::endl;
        std::exit(1);
    }

    std::cout << "Mesh: " << m_fileName << " has been loaded succesfully." << std::endl;
}

int Mesh::loadObj()
{
    std::vector<vec3> vertices;
    std::vector<vec3> normals;
    std::vector<face> indices;

    std::ifstream file;
    std::string line;

    file.open(m_fileName);

    if (file.is_open())
    {
        while (file.good())
        {
            std::getline(file, line);

            if (line.substr(0, 2) == "v ")
            {
                std::istringstream s(line.substr(2));
                vec3 v;
                s >> v.x;
                s >> v.y;
                s >> v.z;
                vertices.push_back(v);
            }
            else if (line.substr(0, 2) == "vn ")
            {
                std::istringstream s(line.substr(2));
                vec3 n;
                s >> n.x;
                s >> n.y;
                s >> n.z;
                normals.push_back(n);
            }
            else if (line.substr(0, 2) == "f ")
            {
                if (line.find("//") == std::string::npos)
                {
                    std::istringstream s(line.substr(2));
                    face f;
                    s >> f.va;
                    s >> f.vb;
                    s >> f.vc;
                    f.va--;
                    f.vb--;
                    f.vc--;
                    indices.push_back(f);
                }
                else
                {
                    std::replace(line.begin(), line.end(), '/', ' ');
                    std::istringstream s(line.substr(2));
                    face f;
                    s >> f.va;
                    s >> f.na;
                    s >> f.vb;
                    s >> f.nb;
                    s >> f.vc;
                    s >> f.nc;
                    f.va--;
                    f.na--;
                    f.vb--;
                    f.nb--;
                    f.vc--;
                    f.nc--;
                    indices.push_back(f);
                }
            }
            else
            {
                continue;
            }
        }
    }
    else
    {
        return 1;
    }

    for (size_t i = 0; i < indices.size(); i++)
    {
        vec3 v0 = vertices[indices[i].va];
        vec3 v1 = vertices[indices[i].vb];
        vec3 v2 = vertices[indices[i].vc];
        if (normals.size() > 0)
        {
            vec3 n0 = normals[indices[i].na];
            vec3 n1 = normals[indices[i].nb];
            vec3 n2 = normals[indices[i].nc];
            m_triangles.push_back(Triangle(v0, v1, v2, n0, n1, n2, m_material));
        }
        else
        {
            m_triangles.push_back(Triangle(v0, v1, v2, m_material));
        }
    }

    return 0;
}
