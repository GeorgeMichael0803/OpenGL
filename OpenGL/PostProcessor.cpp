#include "PostProcessor.h"
#include "WindowController.h"
#include "Shader.h"

void PostProcessor::Cleanup()
{
    glDeleteFramebuffers(1, &framebuffer);
    glDeleteTextures(1, &textureColorbuffer);
    glDeleteRenderbuffers(1, &renderBufferObject);
}

void PostProcessor::Create(Shader* _postShader)
{
    postShader = _postShader;
    CreateBuffers();
    CreateVertices();
}

void PostProcessor::CreateBuffers()
{
    // Framebuffer configuration
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    // Create a color attachment texture
    glGenTextures(1, &textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    Resolution r = WindowController::GetInstance().GetResolution();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, r.width, r.height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

    // Create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    glGenRenderbuffers(1, &renderBufferObject);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBufferObject);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, r.width, r.height); // Use a single renderbuffer object for both a depth AND stencil buffer
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBufferObject); // Now actually attach it

    // Now that we created the framebuffer and added all attachments we want to check if it is complete
    M_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is not complete!");
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void PostProcessor::CreateVertices()
{
    float vertexData[] = { // Vertex attributes for a quad that fills
        // the entire screen in Normalized Device Coordinates.
// positions   // texCoords
-1.0f,  1.0f,   0.0f, 1.0f,
-1.0f, -1.0f,   0.0f, 0.0f,
 1.0f, -1.0f,   1.0f, 0.0f,

-1.0f,  1.0f,   0.0f, 1.0f,
 1.0f, -1.0f,   1.0f, 0.0f,
 1.0f,  1.0f,   1.0f, 1.0f
    };

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), &vertexData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void PostProcessor::BindVertices()
{
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); // Bind the vertex buffer

    // 1st attribute buffer: vertices
    glEnableVertexAttribArray(postShader->GetAttrVertices());
    glVertexAttribPointer(postShader->GetAttrVertices(), // The attribute we want to configure
        2,                   // size (2 components)
        GL_FLOAT,            // type
        GL_FALSE,            // normalized?
        4 * sizeof(float),   // stride floats per vertex definition
        (void*)0);           // array buffer offset

    // 2nd attribute buffer: texCoords
    glEnableVertexAttribArray(postShader->GetAttrTexCoords());
    glVertexAttribPointer(postShader->GetAttrTexCoords(), // The attribute we want to configure
        2,                   // size (2 components)
        GL_FLOAT,            // type
        GL_FALSE,            // normalized?
        4 * sizeof(float),   // stride floats per vertex definition
        (void*)(2 * sizeof(float))); // array buffer offset
}

void PostProcessor::Start()
{
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
}

void PostProcessor::End()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST); // Disable depth test so screen-space quad isn't discarded due to depth test.

    glUseProgram(postShader->GetProgramID()); // Use our shader
    postShader->SetTextureSampler("screenTexture", GL_TEXTURE0, 0, textureColorbuffer);
    BindVertices();
    /*glLineWidth(5.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(postShader->GetAttrVertices());
    glDisableVertexAttribArray(postShader->GetAttrTexCoords());
}
