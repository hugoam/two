using System.Collections.Generic;
using uint32_t = System.Int32;

[Flags] public enum Tag : EntTags
{
	Tag1 = 1 << 0,
	Tag2 = 1 << 1,
	Tag3 = 1 << 2,
	// add your tags
}
class TagsManager
{
    HashSet<uint32_t>[] tags_ = new HashSet<uint32_t>[32];

    public TagsManager()
    {
        for (int i = 0; i < 32; i++)
            tags_[i] = new HashSet<uint32_t>(1 << 10);
    }

    private static int TagToArrIdx(Tag tag)
    {
        return BitUtils.BitPosition((uint)tag);
    }

    public bool AddTagToEntIdx(uint32_t e, Tag t)
    {
        return tags_[TagToArrIdx(t)].Add(e);
    }

    public bool RemoveTagFromEntIdx(uint32_t e, Tag t)
    {
        return tags_[TagToArrIdx(t)].Remove(e);
    }

    public void RemoveAllTagsFromEntIdx(uint32_t e)
    {
        for (auto i = 0; i < tags_.size(); i++)
            tags_[i].Remove(e);
    }

    public HashSet<uint32_t> GetEntIdxsWithTag(Tag tag)
    {
        return tags_[TagToArrIdx(tag)];
    }

}