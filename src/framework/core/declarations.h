/*
 * Copyright (c) 2010-2012 OTClient <https://github.com/edubart/otclient>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef FRAMEWORK_CORE_DECLARATIONS_H
#define FRAMEWORK_CORE_DECLARATIONS_H

#include <framework/global.h>

class ModuleManager;
class ResourceManager;
class Module;
class Event;
class ScheduledEvent;
class FileStream;
class BinaryTree;
class BinaryWriteTree;

typedef stdext::shared_object_ptr<Module> ModulePtr;
typedef stdext::shared_object_ptr<Event> EventPtr;
typedef stdext::shared_object_ptr<ScheduledEvent> ScheduledEventPtr;
typedef stdext::shared_object_ptr<FileStream> FileStreamPtr;
typedef stdext::shared_object_ptr<BinaryTree> BinaryTreePtr;
typedef stdext::shared_object_ptr<BinaryWriteTree> BinaryWriteTreePtr;

typedef std::vector<BinaryTreePtr> BinaryTreeVec;

#endif
