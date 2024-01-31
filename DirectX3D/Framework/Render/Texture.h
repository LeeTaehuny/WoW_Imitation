#pragma once

class Texture
{
private:
    Texture(ID3D11ShaderResourceView* srv, ScratchImage& image, wstring file);
    ~Texture();

public:
    void PSSet(UINT slot = 0);
    void DSSet(UINT slot = 0);

    Vector2 GetSize()
    {
        return Vector2(image.GetMetadata().width, image.GetMetadata().height);
    }

    void ReadPixels(vector<Float4>& pixels);

    wstring GetFile() { return file; }
    ID3D11ShaderResourceView* GetSRV() { return srv; }

public:
    static Texture* Add(wstring file);
    static Texture* Add(wstring file, wstring key);
    static Texture* Add(wstring key, ID3D11ShaderResourceView* srv);

    static void Delete();

private:
    wstring file;

    ScratchImage image;
    ID3D11ShaderResourceView* srv;

    bool isReferenced;

    static unordered_map<wstring, Texture*> textures;
};