using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AudioController : MonoBehaviour
{
    public List<AudioSource> audio_sources = new List<AudioSource>();
    public float offset;
    void Start()
    {
        StartCoroutine(sound());
    }
    public IEnumerator sound()
    {
        while (true){
            yield return new WaitForSeconds(audio_sources[0].clip.length-offset);
            audio_sources[1].Play();
            yield return new WaitForSeconds(offset);
        }
    }
}