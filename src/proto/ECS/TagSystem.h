using System.Collections.Generic;
using EntIdx = System.Int32;

[Flags] public enum Tag : EntTags
{
	Tag1 = 1 << 0,
	Tag2 = 1 << 1,
	Tag3 = 1 << 2,
	// add your tags
}
class TagsManager
{
    HashSet<EntIdx>[] tags_ = new HashSet<EntIdx>[32];

    public TagsManager()
    {
        for (int i = 0; i < 32; i++)
            tags_[i] = new HashSet<EntIdx>(1 << 10);
    }

    private static int TagToArrIdx(Tag tag)
    {
        return BitUtils.BitPosition((uint)tag);
    }

    public bool AddTagToEntIdx(EntIdx e, Tag t)
    {
        return tags_[TagToArrIdx(t)].Add(e);
    }

    public bool RemoveTagFromEntIdx(EntIdx e, Tag t)
    {
        return tags_[TagToArrIdx(t)].Remove(e);
    }

    public void RemoveAllTagsFromEntIdx(EntIdx e)
    {
        for (auto i = 0; i < tags_.size(); i++)
            tags_[i].Remove(e);
    }

    public HashSet<EntIdx> GetEntIdxsWithTag(Tag tag)
    {
        return tags_[TagToArrIdx(tag)];
    }

}