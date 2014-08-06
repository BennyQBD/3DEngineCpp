/*
 * Copyright (C) 2014 Benny Bobaganoosh
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "math3d.h"

Vector3f Vector3f::Rotate(const Quaternion& rotation) const
{
	Quaternion conjugateQ = rotation.Conjugate();
	Quaternion w = rotation * (*this) * conjugateQ;

	Vector3f ret(w.GetX(), w.GetY(), w.GetZ());

	return ret;
}
