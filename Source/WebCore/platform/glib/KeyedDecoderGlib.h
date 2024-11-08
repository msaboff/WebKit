/*
 * Copyright (C) 2015 Igaia S.L.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef KeyedDecoderGlib_h
#define KeyedDecoderGlib_h

#include "KeyedCoding.h"
#include <glib.h>
#include <wtf/HashMap.h>
#include <wtf/glib/GRefPtr.h>
#include <wtf/text/StringHash.h>
#include <wtf/text/WTFString.h>

namespace WebCore {

class KeyedDecoderGlib final : public KeyedDecoder {
public:
    KeyedDecoderGlib(std::span<const uint8_t> data);
    ~KeyedDecoderGlib() override;

private:
    WARN_UNUSED_RETURN bool decodeBytes(const String& key, std::span<const uint8_t>&) override;
    WARN_UNUSED_RETURN bool decodeBool(const String& key, bool&) override;
    WARN_UNUSED_RETURN bool decodeUInt32(const String& key, uint32_t&) override;
    WARN_UNUSED_RETURN bool decodeUInt64(const String& key, uint64_t&) override;
    WARN_UNUSED_RETURN bool decodeInt32(const String& key, int32_t&) override;
    WARN_UNUSED_RETURN bool decodeInt64(const String& key, int64_t&) override;
    WARN_UNUSED_RETURN bool decodeFloat(const String& key, float&) override;
    WARN_UNUSED_RETURN bool decodeDouble(const String& key, double&) override;
    WARN_UNUSED_RETURN bool decodeString(const String& key, String&) override;

    bool beginObject(const String& key) override;
    void endObject() override;

    bool beginArray(const String& key) override;
    bool beginArrayElement() override;
    void endArrayElement() override;
    void endArray() override;

    template<typename T, typename F> WARN_UNUSED_RETURN bool decodeSimpleValue(const String& key, T& result, F getFunction);
    UncheckedKeyHashMap<String, GRefPtr<GVariant>> dictionaryFromGVariant(GVariant*);

    Vector<UncheckedKeyHashMap<String, GRefPtr<GVariant>>> m_dictionaryStack;
    Vector<GVariant*, 16> m_arrayStack;
    Vector<unsigned> m_arrayIndexStack;
};

} // namespace WebCore

#endif // KeyedDecoderGlib_h
